#include "Select.h"


etool_select* etool_select_create(int size)
{
	etool_select *selectfd = malloc(sizeof(etool_select));
	if (selectfd == 0) { return 0; }
#if defined(_windows)
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	selectfd->fd = epoll_create(size);
#endif
	return selectfd;
}

int etool_select_load(etool_select *selectfd, int size)
{
#if defined(_windows)
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	selectfd->fd = epoll_create(size);
#endif
	return 0;
}

void etool_select_unload(etool_select *selectfd)
{
#if defined(_windows)
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	close(selectfd->fd);
#endif
}

void etool_select_destroy(etool_select *selectfd)
{
#if defined(_windows)
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	close(selectfd->fd);
#endif
	free(selectfd);
}

int etool_select_add(etool_select *selectfd, etool_socket *socketfd, etool_selectType type)
{
#if defined(_windows)
	//首先将这个socketfd设置为非阻塞
	unsigned long on = 1;
	if (ioctlsocket(socketfd->fd, FIONBIO, &on) != 0) {
		return -1;
	}
	return 0;
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	//首先将这个socketfd设置为非阻塞
	int opts = fcntl(socketfd->fd, F_GETFL);
	if (opts != 0) { return -1; }
	if (fcntl(socketfd->fd, F_SETFL, opts | O_NONBLOCK) != 0) {
		return -1;
	}
	struct epoll_event ev;
	ev.data.ptr = socketfd;
	ev.data.fd = socketfd->fd;
	switch (type) {
	case ETOOL_SELECT_RECV :
		ev.events = EPOLLIN;
		break;
	case ETOOL_SELECT_SEND :
		ev.events = EPOLLOUT;
		break;
	case ETOOL_SELECT_LISTEN :
		ev.events = EPOLLIN | EPOLLET;
		break;
	case ETOOL_SELECT_ALL :
		ev.events = EPOLLIN | EPOLLOUT;
		break;
	default :
		return -1;
	}
	return epoll_ctl(selectfd->fd, EPOLL_CTL_ADD, socketfd->fd, &ev);
#endif
}

int etool_select_mod(etool_select *selectfd, etool_socket *socketfd, etool_selectType type)
{
#if defined(_windows)
	return 0;
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	struct epoll_event ev;
	ev.data.ptr = socketfd;
	ev.data.fd = socketfd->fd;
	switch (type) {
	case ETOOL_SELECT_RECV :
		ev.events = EPOLLIN;
		break;
	case ETOOL_SELECT_SEND :
		ev.events = EPOLLOUT;
		break;
	case ETOOL_SELECT_LISTEN :
		ev.events = EPOLLIN | EPOLLET;
		break;
	case ETOOL_SELECT_ALL :
		ev.events = EPOLLIN | EPOLLOUT;
		break;
	default :
		return -1;
	}
	return epoll_ctl(selectfd->fd, EPOLL_CTL_MOD, socketfd->fd, &ev);
#endif	
}

int etool_select_del(etool_select *selectfd, etool_socket *socketfd, etool_selectType type)
{
#if defined(_windows)
	return 0;
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	struct epoll_event ev;
	ev.data.ptr = socketfd;
	ev.data.fd = socketfd->fd;
	switch (type) {
	case ETOOL_SELECT_RECV :
		ev.events = EPOLLIN;
		break;
	case ETOOL_SELECT_SEND :
		ev.events = EPOLLOUT;
		break;
	case ETOOL_SELECT_LISTEN :
		ev.events = EPOLLIN | EPOLLET;
		break;
	case ETOOL_SELECT_ALL :
		ev.events = EPOLLIN | EPOLLOUT;
		break;
	default :
		return -1;
	}
	return epoll_ctl(selectfd->fd, EPOLL_CTL_DEL, socketfd->fd, &ev);
#endif
}

void etool_select_wait(etool_select *selectfd, etool_selectCallback *callback, const int timeout)
{
#if defined(_windows)
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	struct epoll_event events[ETOOL_SELECT_SIZE];
	int n, nfds = epoll_wait(selectfd->fd, events, ETOOL_SELECT_SIZE, timeout);
	for (n = 0; n < nfds; n++) {
		switch (events[n].events) {
		case EPOLLIN :
			callback(events[n].data.ptr, ETOOL_SELECT_RECV);
			break;
		case EPOLLOUT :
			callback(events[n].data.ptr, ETOOL_SELECT_SEND);
			break;
		case EPOLLIN | EPOLLET :
			callback(events[n].data.ptr, ETOOL_SELECT_LISTEN);
			break;
		case EPOLLIN | EPOLLOUT :
			callback(events[n].data.ptr, ETOOL_SELECT_ALL);
			break;
		default :
			epoll_ctl(selectfd->fd, EPOLL_CTL_DEL, events[n].data.fd, events + n);
			//continue;
		}
	}
#endif
}
