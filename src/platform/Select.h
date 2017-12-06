/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 标准的多路复用(epoll,iocp)封装
 */

#ifndef ETOOL_PLATFORM_SELECT
#define ETOOL_PLATFORM_SELECT

#include <stdlib.h>
#if defined(_windows)
#include <winsock2.h>
#include <windows.h>
#endif
#if defined(_linux) || defined(_android)
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "../type/CircQueue.h"
#endif
#if defined(_mac) || defined(_ios)
#include <fcntl.h>
#include <unistd.h>
#include <sys/event.h>
#include "../type/CircQueue.h"
#endif

typedef struct _etool_socket etool_socket;
typedef struct _etool_socketIo etool_socketIo;
typedef enum _etool_socketOp etool_socketOp;

#define ETOOL_SELECT_SIZE 20
#if defined(_linux) || defined(_android)
#define ETOOL_SELECT_MOD(selectfd, sockfd, op) \
struct epoll_event ev; \
ev.data.ptr = sockfd; \
ev.data.fd = sockfd->fd; \
switch (op) { \
case ETOOL_SOCKET_SEND : \
case ETOOL_SOCKET_SENDTO : \
	ev.events = EPOLLOUT; \
	break; \
case ETOOL_SOCKET_RECV : \
case ETOOL_SOCKET_RECVFROM : \
case ETOOL_SOCKET_ACCEPT : \
	ev.events = EPOLLIN; \
	break; \
default : \
	break; \
} \
epoll_ctl(selectfd->fd, EPOLL_CTL_MOD, sockfd->fd, &ev)
#endif
#if defined(_mac) || defined(_ios)
#define ETOOL_SELECT_MOD(selectfd, sockfd, op) \
struct kevent ev; \
switch (op) { \
case ETOOL_SOCKET_SEND : \
case ETOOL_SOCKET_SENDTO : \
	EV_SET(&ev, sockfd->fd, EVFILT_WRITE, EV_CLEAR, 0, 0, (void*)sockfd); \
	break; \
case ETOOL_SOCKET_RECV : \
case ETOOL_SOCKET_RECVFROM : \
case ETOOL_SOCKET_ACCEPT : \
	EV_SET(&ev, sockfd->fd, EVFILT_READ, EV_CLEAR, 0, 0, (void*)sockfd); \
	break; \
default : \
	break; \
} \
kevent(selectfd->fd, &ev, 1, 0, 0, 0)
#endif

typedef struct _etool_select {
#if defined(_windows)
	HANDLE fd;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	int fd;
#endif
} etool_select;
typedef void etool_selectCallback(etool_socket *sockfd, etool_socketIo *io, char *data, int length, etool_socketOp op);

/**
 * 创建select
 * @param  size       [description]
 * @return            [description]
 */
etool_select* etool_select_create(int size);

/**
 * 创建select
 * @param  size       [description]
 * @param  selectfd   [description]
 * @return            [description]
 */
int etool_select_load(etool_select *selectfd, int size);

/**
 * 创建select
 * @param  selectfd   [description]
 */
void etool_select_unload(etool_select *selectfd);

/**
 * 销毁select
 * @param  selectfd   [description]
 * @return            [description]
 */
void etool_select_destroy(etool_select *selectfd);

/**
 * 添加socket
 * @param  selectfd   [description]
 * @param  sockfd   [description]
 * @param  type       [description]
 * @return 
 */
int etool_select_bind(etool_select *selectfd, etool_socket *sockfd, etool_socketOp op);

/**
 * 删除socket
 * @param  selectfd   [description]
 * @param  sockfd   [description]
 * @param  type       [description]
 * @return 
 */
int etool_select_unbind(etool_select *selectfd, etool_socket *sockfd, etool_socketOp op);

/**
 * 等待轮询
 * @param  selectfd   [description]
 * @param  callback   [description]
 * @param  timeout    [description] 
 */
void etool_select_wait(etool_select *selectfd, etool_selectCallback *callback, const int timeout);

#endif //ETOOL_PLATFORM_SELECT


/**
 * 修改socket
 * @param  selectfd   [description]
 * @param  sockfd   [description]
 * @param  type       [description]
 * @return 
 */
// int etool_select_mod(etool_select *selectfd, etool_socket *sockfd, etool_socketOp op);
