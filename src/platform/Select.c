#include "Select.h"
#include "Socket.h"

etool_select* etool_select_create(int size)
{
	etool_select *selectfd = malloc(sizeof(etool_select));
	if (selectfd == 0) { return 0; }
#if defined(_windows)
	selectfd->fd = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
#endif

#if defined(_linux) || defined(_android)
	selectfd->fd = epoll_create(size);
#endif

#if defined(_mac) || defined(_ios)
	selectfd->fd = kqueue();
#endif
	return selectfd;
}

int etool_select_load(etool_select *selectfd, int size)
{
#if defined(_windows)
	selectfd->fd = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
#endif

#if defined(_linux) || defined(_android)
	selectfd->fd = epoll_create(size);
#endif

#if defined(_mac) || defined(_ios)
	selectfd->fd = kqueue();
#endif
	return 0;
}

void etool_select_unload(etool_select *selectfd)
{
#if defined(_windows)
	CloseHandle(selectfd->fd);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	close(selectfd->fd);
#endif
}

void etool_select_destroy(etool_select *selectfd)
{
#if defined(_windows)
	CloseHandle(selectfd->fd);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	close(selectfd->fd);
#endif
	free(selectfd);
}

int etool_select_bind(etool_select *selectfd, etool_socket *sockfd, etool_selectType type)
{
#if defined(_windows)
	switch (type) {
	case ETOOL_SELECT_RECV :
		CreateIoCompletionPort((HANDLE)(sockfd->fd), selectfd->fd, (ULONG_PTR)sockfd, 0);
		break;
	case ETOOL_SELECT_ACCEPT : {
		DWORD bytes;
		LPFN_ACCEPTEX acceptEx;
		GUID guidAcceptEx = WSAID_ACCEPTEX;
		if (WSAIoctl(sockfd->fd, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx,
			sizeof(guidAcceptEx), &acceptEx, sizeof(LPFN_ACCEPTEX), &bytes, 0, 0) != 0) {
			return -1;
		}
		CreateIoCompletionPort((HANDLE)(sockfd->fd), selectfd->fd, (ULONG_PTR)sockfd, 0);
		//需要开启接收
		char *io = malloc(sizeof(OVERLAPPED) + sizeof(etool_selectType) + sizeof(SOCKET) + (sizeof(struct sockaddr_in) + 16) * 2);
		*(etool_selectType*)(io + sizeof(OVERLAPPED)) = ETOOL_SELECT_ACCEPT;
		*(SOCKET*)(io + sizeof(OVERLAPPED) + sizeof(etool_selectType)) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		acceptEx(sockfd->fd, *(SOCKET*)(io + sizeof(OVERLAPPED) + sizeof(etool_selectType)), io + sizeof(OVERLAPPED) + sizeof(etool_selectType) + sizeof(SOCKET),
			0, sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16, 0, (OVERLAPPED*)&io);
		break; }
	case ETOOL_SELECT_SEND :
	case ETOOL_SELECT_RECVFROM :
	case ETOOL_SELECT_SENDTO :
		CreateIoCompletionPort((HANDLE)(sockfd->fd), selectfd->fd, (ULONG_PTR)sockfd, 0);
		break;
	default :
		return -1;
	}
	return 0;
#endif

#if defined(_linux) || defined(_android)
	struct epoll_event ev;
	ev.data.ptr = sockfd;
	ev.data.fd = sockfd->fd;
	switch (type) {
	case ETOOL_SELECT_RECV :
	case ETOOL_SELECT_RECVFROM :
		ev.events = EPOLLIN;
		break;
	case ETOOL_SELECT_ACCEPT :
		ev.events = EPOLLIN | EPOLLET;
		break;
	case ETOOL_SELECT_SEND :
	case ETOOL_SELECT_SENDTO :
		ev.events = EPOLLOUT;
		break;
	default :
		return -1;
	}
	if (etool_socket_nonblock(sockfd, selectfd) != 0) {
		return -1;
	}
	return epoll_ctl(selectfd->fd, EPOLL_CTL_ADD, sockfd->fd, &ev);
#endif

#if defined(_mac) || defined(_ios)
	struct kevent ev;
	switch (type) {
	case ETOOL_SELECT_RECV :
	case ETOOL_SELECT_RECVFROM :
		EV_SET(&ev, sockfd->fd, EVFILT_READ, EV_ADD|EV_ENABLE, 0, 0, (void*)sockfd);
		break;
	case ETOOL_SELECT_ACCEPT :
		EV_SET(&ev, sockfd->fd, EVFILT_READ, EV_ADD|EV_ENABLE, 0, 0, (void*)sockfd);
		break;
	case ETOOL_SELECT_SEND :
	case ETOOL_SELECT_SENDTO :
		EV_SET(&ev, sockfd->fd, EVFILT_WRITE, EV_ADD|EV_ENABLE, 0, 0, (void*)sockfd);
		break;
	default :
		return -1;
	}
	if (etool_socket_nonblock(sockfd, selectfd) != 0) {
		return -1;
	}
	return kevent(selectfd->fd, &ev, 1, 0, 0, 0);
#endif
}

int etool_select_unbind(etool_select *selectfd, etool_socket *sockfd, etool_selectType type)
{
#if defined(_windows)
	static int isInit = 0;
	static LPFN_DISCONNECTEX DisconnectEx;
	if (isInit == 0) {
		DWORD bytes;
		LPFN_DISCONNECTEX DisconnectEx;
		GUID guidDisconnectEx = WSAID_DISCONNECTEX;
		if (WSAIoctl(sockfd->fd, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidDisconnectEx,
			sizeof(guidDisconnectEx), &DisconnectEx, sizeof(LPFN_DISCONNECTEX), &bytes, 0, 0) != 0) {
			return -1;
		}
		isInit = 1;
	}
	DisconnectEx(sockfd->fd, 0, TF_REUSE_SOCKET, 0);
	return 0;
#endif

#if defined(_linux) || defined(_android)
	struct epoll_event ev;
	ev.data.ptr = sockfd;
	ev.data.fd = sockfd->fd;
	switch (type) {
	case ETOOL_SELECT_RECV :
	case ETOOL_SELECT_RECVFROM :
		ev.events = EPOLLIN;
		break;
	case ETOOL_SELECT_SEND :
	case ETOOL_SELECT_SENDTO :
		ev.events = EPOLLOUT;
		break;
	case ETOOL_SELECT_ACCEPT :
		ev.events = EPOLLIN | EPOLLET;
		break;
	default :
		return -1;
	}
	return epoll_ctl(selectfd->fd, EPOLL_CTL_DEL, sockfd->fd, &ev);
#endif

#if defined(_mac) || defined(_ios)
	struct kevent ev;
	switch (type) {
	case ETOOL_SELECT_RECV :
	case ETOOL_SELECT_RECVFROM :
		EV_SET(&ev, sockfd->fd, EVFILT_READ, EV_DELETE, 0, 0, (void*)sockfd);
		break;
	case ETOOL_SELECT_ACCEPT :
		EV_SET(&ev, sockfd->fd, EVFILT_READ, EV_DELETE, 0, 0, (void*)sockfd);
		break;
	case ETOOL_SELECT_SEND :
	case ETOOL_SELECT_SENDTO :
		EV_SET(&ev, sockfd->fd, EVFILT_WRITE, EV_DELETE, 0, 0, (void*)sockfd);
		break;
	default :
		return -1;
	}
	return kevent(selectfd->fd, &ev, 1, 0, 0, 0);
#endif
}

void etool_select_wait(etool_select *selectfd, etool_selectCallback *callback, const int timeout)
{
#if defined(_windows)
	DWORD bytes;
	OVERLAPPED *io;
	etool_socket *sockfd;
	if (GetQueuedCompletionStatus(selectfd->fd, &bytes, (PULONG_PTR)&sockfd, (LPOVERLAPPED*)&io, timeout) == 0) {
		return;
	}
	etool_selectType type = *(etool_selectType*)(io + sizeof(OVERLAPPED));
	switch (type) {
	case ETOOL_SELECT_ACCEPT : {
		etool_socket *acceptSockfd = malloc(sizeof(etool_socket));
		if (acceptSockfd == 0) { return; }
		acceptSockfd->fd = *(SOCKET*)(io + sizeof(OVERLAPPED) + sizeof(etool_selectType));
		if (setsockopt(acceptSockfd->fd, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (const char*)&(sockfd->fd), sizeof(SOCKET)) == SOCKET_ERROR) {
			return;
		}
		callback(acceptSockfd, 0, 0, 0, ETOOL_SELECT_ACCEPT);
		break; }
	case ETOOL_SELECT_RECV :
	case ETOOL_SELECT_SEND :
	case ETOOL_SELECT_RECVFROM :
	case ETOOL_SELECT_SENDTO :
		callback(sockfd, (etool_socketIo*)io, ((etool_socketIo*)io)->buffer.buf, bytes, type);
		break;
	default :
		etool_select_unbind(selectfd, sockfd, type);
		break;
	}
#endif

#if defined(_linux) || defined(_android)
	etool_socketIo *io;
	etool_socket *sockfd;
	struct epoll_event events[ETOOL_SELECT_SIZE];
	int bytes, n, nfds = epoll_wait(selectfd->fd, events, ETOOL_SELECT_SIZE, timeout);
	for (n = 0; n < nfds; n++) {
		sockfd = (etool_socket*)(events[n].data.ptr);
		switch (events[n].events) {
		case EPOLLIN :
			if (etool_circQueue_exit(sockfd->recvBuffer, (void*)&io) != 0) {
				continue;
			}
			if (io->type == ETOOL_SELECT_RECV) {
				bytes = recv(sockfd->fd, io->buf, io->len, 0);
			} else {
				size_t addrlen = sizeof(struct sockaddr);
				bytes = recvfrom(sockfd->fd, io->buf, io->len, 0, (struct sockaddr*)&(io->addr), (socklen_t*)&addrlen);
			}
			callback(sockfd, io, io->buf, bytes, io->type);
			break;
		case EPOLLIN | EPOLLET : {
			struct sockaddr_in addr;
			etool_socket *acceptSockfd = malloc(sizeof(etool_socket));
			if (acceptSockfd == 0) { continue; }
			size_t addrlen = sizeof(struct sockaddr);
			acceptSockfd->fd = accept(sockfd->fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen);
			callback(acceptSockfd, 0, 0, 0, ETOOL_SELECT_ACCEPT);
			break; }
		case EPOLLOUT :
			if (etool_circQueue_get(sockfd->sendBuffer, (void*)&io) != 0) {
				ETOOL_SELECT_MOD(sockfd->selectfd, sockfd, ETOOL_SELECT_RECV);
				continue;
			}
			if (io->type == ETOOL_SELECT_SEND) {
				bytes = send(sockfd->fd, io->buf + io->use, io->len - io->use, 0);
			} else {
				bytes = sendto(sockfd->fd, io->buf + io->use, io->len - io->use, 0, (struct sockaddr*)&(io->addr), sizeof(struct sockaddr));
			}
			io->use += bytes;
			if (io->use == io->len) {
				etool_circQueue_exit(sockfd->sendBuffer, 0);
				if (bytes == 0) { io->use = -io->use; }
				callback(sockfd, io, io->buf, io->use, io->type);
			}
			break;
		default :
			etool_select_unbind(selectfd, sockfd, io->type);
			break;
		}
	}
#endif

#if defined(_mac) || defined(_ios)
	etool_socketIo *io;
	etool_socket *sockfd;
	struct kevent events[ETOOL_SELECT_SIZE];
	struct timespec _timeout;
	_timeout.tv_sec = timeout / 1000;
	_timeout.tv_nsec = (timeout % 1000) * 1000 * 1000;
	int bytes, n, nfds = kevent(selectfd->fd, 0, 0, events, ETOOL_SELECT_SIZE, &_timeout);
	for (n = 0; n < nfds; n++) {
		sockfd = (etool_socket*)(events[n].udata);
		switch (events[n].filter) {
		case EVFILT_READ :
			if (etool_circQueue_exit(sockfd->recvBuffer, (void*)&io) != 0) {
				continue;
			}
			if (io->type == ETOOL_SELECT_RECV) {
				bytes = recv(sockfd->fd, io->buf, io->len, 0);
			} else {
				size_t addrlen = sizeof(struct sockaddr);
				bytes = recvfrom(sockfd->fd, io->buf, io->len, 0, (struct sockaddr*)&(io->addr), (socklen_t*)&addrlen);
			}
			callback(sockfd, io, io->buf, bytes, io->type);
			break;
		// case EPOLLIN | EPOLLET : {
		// 	struct sockaddr_in addr;
		// 	etool_socket *acceptSockfd = malloc(sizeof(etool_socket));
		// 	if (acceptSockfd == 0) { continue; }
		// 	size_t addrlen = sizeof(struct sockaddr);
		// 	acceptSockfd->fd = accept(sockfd->fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen);
		// 	callback(acceptSockfd, 0, 0, 0, ETOOL_SELECT_ACCEPT);
		// 	break; }
		case EVFILT_WRITE :
			if (etool_circQueue_get(sockfd->sendBuffer, (void*)&io) != 0) {
				ETOOL_SELECT_MOD(sockfd->selectfd, sockfd, ETOOL_SELECT_RECV);
				continue;
			}
			if (io->type == ETOOL_SELECT_SEND) {
				bytes = send(sockfd->fd, io->buf + io->use, io->len - io->use, 0);
			} else {
				bytes = sendto(sockfd->fd, io->buf + io->use, io->len - io->use, 0, (struct sockaddr*)&(io->addr), sizeof(struct sockaddr));
			}
			io->use += bytes;
			if (io->use == io->len) {
				etool_circQueue_exit(sockfd->sendBuffer, 0);
				if (bytes == 0) { io->use = -io->use; }
				callback(sockfd, io, io->buf, io->use, io->type);
			}
			break;
		default :
			etool_select_unbind(selectfd, sockfd, io->type);
			break;
		}
	}
#endif
}
