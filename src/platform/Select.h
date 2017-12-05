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
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "../type/CircQueue.h"
#endif

typedef struct _etool_socket etool_socket;
typedef struct _etool_socketIo etool_socketIo;

#define ETOOL_SELECT_SIZE 20
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#define ETOOL_SELECT_MOD(selectfd, sockfd, type) \
struct epoll_event ev; \
ev.data.ptr = sockfd; \
ev.data.fd = sockfd->fd; \
switch (type) { \
case ETOOL_SELECT_RECV : \
	ev.events = EPOLLIN; \
	break; \
case ETOOL_SELECT_SEND : \
	ev.events = EPOLLOUT; \
	break; \
case ETOOL_SELECT_ACCEPT : \
	ev.events = EPOLLIN | EPOLLET; \
	break; \
default : \
	break; \
} \
epoll_ctl(selectfd->fd, EPOLL_CTL_MOD, sockfd->fd, &ev)
#endif

typedef struct _etool_select {
#if defined(_windows)
	HANDLE fd;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	int fd;
#endif
} etool_select;

typedef enum {
	ETOOL_SELECT_RECV = 0,
	ETOOL_SELECT_RECVFROM,
	ETOOL_SELECT_ACCEPT,
	ETOOL_SELECT_SEND,
	ETOOL_SELECT_SENDTO
} etool_selectType;
typedef void etool_selectCallback(etool_socket *sockfd, etool_socketIo *io, char *data, int length, etool_selectType type);

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
int etool_select_bind(etool_select *selectfd, etool_socket *sockfd, etool_selectType type);

/**
 * 删除socket
 * @param  selectfd   [description]
 * @param  sockfd   [description]
 * @param  type       [description]
 * @return 
 */
int etool_select_unbind(etool_select *selectfd, etool_socket *sockfd, etool_selectType type);

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
// int etool_select_mod(etool_select *selectfd, etool_socket *sockfd, etool_selectType type);
