#include "Select.h"
#include "Socket.h"

etool_select* etool_select_create(const int size)
{
	etool_select *selectfd = (etool_select*)malloc(sizeof(etool_select));
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
	if (selectfd->fd == 0) {
		free(selectfd);
		return 0;
	}
	return selectfd;
}

int etool_select_load(etool_select *selectfd, const int size)
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
	if (selectfd->fd == 0) {
		return -1;
	}
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

int etool_select_bind(etool_select *selectfd, etool_socket *sockfd, const etool_socketOp op)
{
#if defined(_windows)
	switch (op) {
	case ETOOL_SOCKET_RECV :
	case ETOOL_SOCKET_ACCEPT :
	case ETOOL_SOCKET_SEND :
	case ETOOL_SOCKET_RECVFROM :
	case ETOOL_SOCKET_SENDTO :
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
	switch (op) {
	case ETOOL_SOCKET_RECV :
	case ETOOL_SOCKET_RECVFROM :
	case ETOOL_SOCKET_ACCEPT :
		ev.events = EPOLLIN;
		break;
	case ETOOL_SOCKET_SEND :
	case ETOOL_SOCKET_SENDTO :
		ev.events = EPOLLOUT;
		break;
	default :
		return -1;
	}
	if (etool_socket_nonblock(sockfd, selectfd, op) != 0) {
		return -1;
	}
	return epoll_ctl(selectfd->fd, EPOLL_CTL_ADD, sockfd->fd, &ev);
#endif

#if defined(_mac) || defined(_ios)
	struct kevent ev;
	switch (op) {
	case ETOOL_SOCKET_RECV :
	case ETOOL_SOCKET_RECVFROM :
	case ETOOL_SOCKET_ACCEPT :
		EV_SET(&ev, sockfd->fd, EVFILT_READ, EV_ADD|EV_ENABLE, 0, 0, (void*)sockfd);
		break;
	case ETOOL_SOCKET_SEND :
	case ETOOL_SOCKET_SENDTO :
		EV_SET(&ev, sockfd->fd, EVFILT_WRITE, EV_ADD|EV_ENABLE, 0, 0, (void*)sockfd);
		break;
	default :
		return -1;
	}
	if (etool_socket_nonblock(sockfd, selectfd, op) != 0) {
		return -1;
	}
	return kevent(selectfd->fd, &ev, 1, 0, 0, 0);
#endif
}

int etool_select_unbind(etool_select *selectfd, etool_socket *sockfd, const etool_socketOp op)
{
#if defined(_windows)
	// static short isInit = 0;
	// static LPFN_DISCONNECTEX DisconnectEx;
	// if (isInit == 0) {
	// 	DWORD bytes;
	// 	GUID guidDisconnectEx = WSAID_DISCONNECTEX;
	// 	if (WSAIoctl(sockfd->fd, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidDisconnectEx,
	// 		sizeof(guidDisconnectEx), &DisconnectEx, sizeof(LPFN_DISCONNECTEX), &bytes, 0, 0) != 0) {
	// 		return -1;
	// 	}
	// 	isInit = 1;
	// }
	// DisconnectEx(sockfd->fd, 0, TF_REUSE_SOCKET, 0);
	return 0;
#endif

#if defined(_linux) || defined(_android)
	struct epoll_event ev;
	ev.data.ptr = sockfd;
	ev.data.fd = sockfd->fd;
	switch (op) {
	case ETOOL_SOCKET_RECV :
	case ETOOL_SOCKET_RECVFROM :
	case ETOOL_SOCKET_ACCEPT :
		ev.events = EPOLLIN;
		break;
	case ETOOL_SOCKET_SEND :
	case ETOOL_SOCKET_SENDTO :
		ev.events = EPOLLOUT;
		break;
	default :
		return -1;
	}
	return epoll_ctl(selectfd->fd, EPOLL_CTL_DEL, sockfd->fd, &ev);
#endif

#if defined(_mac) || defined(_ios)
	struct kevent ev;
	switch (op) {
	case ETOOL_SOCKET_RECV :
	case ETOOL_SOCKET_RECVFROM :
	case ETOOL_SOCKET_ACCEPT :
		EV_SET(&ev, sockfd->fd, EVFILT_READ, EV_DELETE, 0, 0, (void*)sockfd);
		break;
	case ETOOL_SOCKET_SEND :
	case ETOOL_SOCKET_SENDTO :
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
	etool_socketIo *io;
	etool_socket *sockfd;
	if (GetQueuedCompletionStatus(selectfd->fd, &bytes, (PULONG_PTR)&sockfd, (LPOVERLAPPED*)&io, timeout) == 0) {
		return;
	}
	switch (io->op) {
	case ETOOL_SOCKET_ACCEPT : {
		void **_addr = ((etool_socketSingle*)(sockfd->ptr))->_addr;
		etool_socket *acceptSockfd = (etool_socket*)(io->buffer.buf);
		if (setsockopt(acceptSockfd->fd, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (const char*)&(sockfd->fd), sizeof(SOCKET)) == SOCKET_ERROR) {
			return;
		}
		static short isInit = 0;
		static LPFN_GETACCEPTEXSOCKADDRS GETACCEPTEXSOCKADDRS;
		if (isInit == 0) {
			DWORD bytes;
			GUID guidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
			if (WSAIoctl(sockfd->fd, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidGetAcceptExSockaddrs,
				sizeof(GUID), &GETACCEPTEXSOCKADDRS, sizeof(LPFN_GETACCEPTEXSOCKADDRS), &bytes, 0, 0) == 0) {
				isInit = 1;
			}
		} else {
			struct sockaddr_in *addr;
			int addrlen = sizeof(struct sockaddr);
			GETACCEPTEXSOCKADDRS(((etool_socketSingle*)(sockfd->ptr))->addr,
				0, sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16, 0, 0, (LPSOCKADDR*)&addr, &addrlen);
			*(char**)_addr[0] = inet_ntoa(addr->sin_addr);
			*(short*)_addr[1] = ntohs(addr->sin_port);
		}
		callback(acceptSockfd, io, (char*)_addr, 2, ETOOL_SOCKET_ACCEPT);
		break; }
	case ETOOL_SOCKET_RECV :
	case ETOOL_SOCKET_SEND :
	case ETOOL_SOCKET_RECVFROM :
	case ETOOL_SOCKET_SENDTO :
		callback(sockfd, (etool_socketIo*)io, ((etool_socketIo*)io)->buffer.buf, bytes, io->op);
		break;
	default :
		etool_select_unbind(selectfd, sockfd, io->op);
		break;
	}
#endif

#if defined(_linux) || defined(_android)
	etool_socketIo *io = 0;
	etool_socket *sockfd;
	struct epoll_event events[ETOOL_SELECT_SIZE];
	int bytes, n, nfds = epoll_wait(selectfd->fd, events, ETOOL_SELECT_SIZE, timeout);
	for (n = 0; n < nfds; n++) {
		sockfd = (etool_socket*)(events[n].data.ptr);
		switch (events[n].events) {
		case EPOLLIN :
			if (sockfd->state == 0) {
				//recv
				if (etool_circQueue_empty(&(((etool_socketConnect*)(sockfd->ptr))->recvQueue))) {
					continue;
				}
				etool_circQueue_exit(&(((etool_socketConnect*)(sockfd->ptr))->recvQueue), io, etool_socketIo*);
				if (io->op == ETOOL_SOCKET_RECV) {
					bytes = recv(sockfd->fd, io->buf, io->len, 0);
				} else {
					size_t addrlen = sizeof(struct sockaddr);
					bytes = recvfrom(sockfd->fd, io->buf, io->len, 0, (struct sockaddr*)&(io->addr), (socklen_t*)&addrlen);
				}
				callback(sockfd, io, io->buf, bytes, io->op);
			} else {
				//accept
				etool_socket *acceptSockfd = (etool_socket*)malloc(sizeof(etool_socket));
				if (acceptSockfd == 0) { continue; }
				void **_addr = ((etool_socketSingle*)(sockfd->ptr))->_addr;
				struct sockaddr_in addr;
				size_t addrlen = sizeof(struct sockaddr);
				acceptSockfd->fd = accept(sockfd->fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen);
				*(char**)_addr[0] = inet_ntoa(addr.sin_addr);
				*(short*)_addr[1] = ntohs(addr.sin_port);
				callback(acceptSockfd, sockfd->state, (char*)_addr, 2, ETOOL_SOCKET_ACCEPT);
			}
			break;
		case EPOLLOUT :
			if (etool_circQueue_empty(&(((etool_socketConnect*)(sockfd->ptr))->sendQueue))) {
				ETOOL_SELECT_MOD(sockfd->selectfd, sockfd, ETOOL_SOCKET_RECV);
				continue;
			}
			etool_circQueue_head(&(((etool_socketConnect*)(sockfd->ptr))->sendQueue), io, etool_socketIo*);
			if (io->op == ETOOL_SOCKET_SEND) {
				bytes = send(sockfd->fd, io->buf + io->use, io->len - io->use, 0);
			} else {
				bytes = sendto(sockfd->fd, io->buf + io->use, io->len - io->use, 0, (struct sockaddr*)&(io->addr), sizeof(struct sockaddr));
			}
			io->use += bytes;
			if (io->use == io->len) {
				etool_circQueue_exit(&(((etool_socketConnect*)(sockfd->ptr))->sendQueue), io, etool_socketIo*);
				if (bytes == 0) { io->use = -io->use; }
				callback(sockfd, io, io->buf, io->use, io->op);
			}
			break;
		default :
			etool_select_unbind(selectfd, sockfd, io->op);
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
			if (sockfd->state == 0) {
				//recv		
				if (etool_circQueue_empty(&(((etool_socketConnect*)(sockfd->ptr))->recvQueue))) {
					continue;
				}
				etool_circQueue_exit(&(((etool_socketConnect*)(sockfd->ptr))->recvQueue), io, etool_socketIo*);
				if (io->op == ETOOL_SOCKET_RECV) {
					bytes = recv(sockfd->fd, io->buf, io->len, 0);
				} else {
					size_t addrlen = sizeof(struct sockaddr);
					bytes = recvfrom(sockfd->fd, io->buf, io->len, 0, (struct sockaddr*)&(io->addr), (socklen_t*)&addrlen);
				}
				callback(sockfd, io, io->buf, bytes, io->op);
			} else {
				//accept
				etool_socket *acceptSockfd = (etool_socket*)malloc(sizeof(etool_socket));
				if (acceptSockfd == 0) { continue; }
				void **_addr = ((etool_socketSingle*)(sockfd->ptr))->_addr;
				struct sockaddr_in addr;
				size_t addrlen = sizeof(struct sockaddr);
				acceptSockfd->fd = accept(sockfd->fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen);
				*(char**)_addr[0] = inet_ntoa(addr.sin_addr);
				*(short*)_addr[1] = ntohs(addr.sin_port);
				callback(acceptSockfd, sockfd->state, (char*)_addr, 2, ETOOL_SOCKET_ACCEPT);
			}
			break;
		case EVFILT_WRITE :
			if (etool_circQueue_empty(&(((etool_socketConnect*)(sockfd->ptr))->sendQueue))) {
				ETOOL_SELECT_MOD(sockfd->selectfd, sockfd, ETOOL_SOCKET_RECV);
				continue;
			}
			etool_circQueue_head(&(((etool_socketConnect*)(sockfd->ptr))->sendQueue), io, etool_socketIo*);
			if (io->op == ETOOL_SOCKET_SEND) {
				bytes = send(sockfd->fd, io->buf + io->use, io->len - io->use, 0);
			} else {
				bytes = sendto(sockfd->fd, io->buf + io->use, io->len - io->use, 0, (struct sockaddr*)&(io->addr), sizeof(struct sockaddr));
			}
			io->use += bytes;
			if (io->use == io->len) {
				etool_circQueue_exit(&(((etool_socketConnect*)(sockfd->ptr))->sendQueue), io, etool_socketIo*);
				if (bytes == 0) { io->use = -io->use; }
				callback(sockfd, io, io->buf, io->use, io->op);
			}
			break;
		default :
			etool_select_unbind(selectfd, sockfd, io->op);
			break;
		}
	}
#endif
}
