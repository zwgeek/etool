/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 标准的多路复用(epoll,iocp)封装
 */

#ifndef ETOOL_PLATFORM_SELECT
#define ETOOL_PLATFORM_SELECT

#include <stdlib.h>
#include "Socket.h"
#if defined(_windows)
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#endif

#define ETOOL_SELECT_SIZE 20

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
	ETOOL_SELECT_SEND,
	ETOOL_SELECT_LISTEN,
	ETOOL_SELECT_ALL
} etool_selectType;
typedef void etool_selectCallback(etool_socket *socketfd, etool_selectType type);

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
 * @param  socketfd   [description]
 * @param  type       [description]
 * @return 
 */
int etool_select_add(etool_select *selectfd, etool_socket *socketfd, etool_selectType type);

/**
 * 修改socket
 * @param  selectfd   [description]
 * @param  socketfd   [description]
 * @param  type       [description]
 * @return 
 */
int etool_select_mod(etool_select *selectfd, etool_socket *socketfd, etool_selectType type);

/**
 * 删除socket
 * @param  selectfd   [description]
 * @param  socketfd   [description]
 * @param  type       [description]
 * @return 
 */
int etool_select_del(etool_select *selectfd, etool_socket *socketfd, etool_selectType type);

/**
 * 等待轮询
 * @param  selectfd   [description]
 * @param  callback   [description]
 * @param  timeout    [description] 
 */
void etool_select_wait(etool_select *selectfd, etool_selectCallback *callback, const int timeout);

#endif //ETOOL_PLATFORM_SELECT