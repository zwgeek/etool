/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于链表方式的(支持双端队列)队列(不使用Memory模块)
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_LINKQUEUE
#define ETOOL_TYPE_LINKQUEUE

#include <stdlib.h>

typedef struct _etool_linkQueue {
	unsigned int typeSize;
	unsigned int length;
	struct _etool_linkNode *front;
	struct _etool_linkNode *rear;
} etool_linkQueue;

struct _etool_linkNode {
	unsigned char *data;
	struct _etool_linkNode *next;
};

typedef struct _etool_linkQueueIterator {
	unsigned char *data;
	struct _etool_linkNode *next;
} etool_linkQueueIterator;

/**
 * 创建queue (动态存储表示)
 * @param  typeSize [not null]
 * @return      [实体]
 */
etool_linkQueue* etool_linkQueue_create(const unsigned int typeSize);

/**
 * 销毁queue (动态存储表示)
 * @param  queue [not null]
 * @return      [error code]
 */
void etool_linkQueue_destroy(etool_linkQueue *queue);

/**
 * 清空queue
 * @param  queue [description]
 * @return      [description]
 */
void etool_linkQueue_clear(etool_linkQueue *queue);

/**
 * 获得queue的有效长度
 * @param  queue [description]
 * @return      [description]
 */
int etool_linkQueue_length(etool_linkQueue *queue);

/**
 * queue是否为空
 * @param  queue [description]
 * @return      [bool code]
 */
int etool_linkQueue_empty(etool_linkQueue *queue);

/**
 * 获取队头元素,O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_linkQueue_get(etool_linkQueue *queue, void *value);

/**
 * 获取队尾元素,O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_linkQueue_peer_get(etool_linkQueue *queue, void *value);

/**
 * 进入队列,O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_linkQueue_enter(etool_linkQueue *queue, const void *value);

/**
 * 进入队列(从队头进入),O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_linkQueue_peer_enter(etool_linkQueue *queue, const void *value);

/**
 * 退出队列,O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_linkQueue_exit(etool_linkQueue *queue, void *value);

/**
 * 退出队列(从队尾退出),O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_linkQueue_peer_exit(etool_linkQueue *queue, void *value);

/**
 * 创建迭代器
 * @param  queue [description]
 * @return         [description]
 */
etool_linkQueueIterator* etool_linkQueueIterator_init(etool_linkQueue *queue);

/**
 * 遍历迭代器
 * @param  iterator [description]
 * @return          [description]
 */
int etool_linkQueueIterator_next(etool_linkQueueIterator *iterator);

#endif //ETOOL_TYPE_LINKQUEUE