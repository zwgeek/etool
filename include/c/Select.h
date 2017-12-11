/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 标准的多路复用(epoll,iocp)封装
 */

#ifndef ETOOL_SELECT
#define ETOOL_SELECT

typedef struct _etool_socket etool_socket;
typedef struct _etool_socketIo etool_socketIo;
typedef enum _etool_socketOp etool_socketOp;

typedef struct _etool_select etool_select;
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

#endif //ETOOL_SELECT
