/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于链表方式的(支持双端队列)队列(不使用Memory模块)
 */

#ifndef ETOOL_TYPE_LINKQUEUE
#define ETOOL_TYPE_LINKQUEUE

#include <stdlib.h>

typedef struct _etool_linkQueue {
	unsigned int length;
	struct _etool_linkNode *front;
	struct _etool_linkNode *rear;
} etool_linkQueue;

#ifndef ETOOL_LINKNODE
#define ETOOL_LINKNODE
struct _etool_linkNode {
	unsigned char *data;
	struct _etool_linkNode *next;
};
#endif


/**
 * etool_linkQueue* etool_linkQueue_create(const unsigned int typeSize);
 * 创建queue (动态存储表示)
 * @param  queue [not null]
 */
#define etool_linkQueue_init(queue) \
do { \
	queue = (etool_linkQueue*)malloc(sizeof(etool_linkQueue)); \
	if (queue != 0) { \
		struct _etool_linkNode *node = (struct _etool_linkNode*)malloc(sizeof(struct _etool_linkNode)); \
		if (node != 0) { \
			node->next = 0; \
			(queue)->length = 0; \
			(queue)->front = node; \
			(queue)->rear = node; \
		} else { \
			free(queue); \
			queue = 0; \
		} \
	} \
} while(0)

/**
 * void etool_linkQueue_destroy(etool_linkQueue *queue);
 * 销毁queue (动态存储表示)
 * @param  queue [not null]
 */
#define etool_linkQueue_free(queue) \
do { \
	struct _etool_linkNode *node; \
	while ((queue)->front->next != 0) { \
		node = (queue)->front->next; \
		(queue)->front->next = node->next; \
		free(node); \
	} \
	free((queue)->front); \
	free(queue); \
	queue = 0; \
} while(0)

/**
 * void etool_linkQueue_clear(etool_linkQueue *queue);
 * 清空queue
 * @param  queue [description]
 */
#define etool_linkQueue_clear(queue) \
do { \
	struct _etool_linkNode *node; \
	while ((queue)->front->next != 0) { \
		node = (queue)->front->next; \
		(queue)->front->next = node->next; \
		free(node); \
	} \
	(queue)->length = 0; \
	(queue)->rear = (queue)->front; \
} while(0)

/**
 * int etool_linkQueue_length(etool_linkQueue *queue);
 * 获得queue的有效长度
 * @param  queue [description]
 */
#define etool_linkQueue_length(queue) \
((queue)->length)

/**
 * int etool_linkQueue_empty(etool_linkQueue *queue);
 * queue是否为空
 * @param  queue [description]
 */
#define etool_linkQueue_empty(queue) \
((queue)->length == 0)

/**
 * int etool_linkQueue_head(etool_linkQueue *queue, void *value);
 * 获取队头元素,O(1)
 * @param  queue [description]
 * @param  value [description]
 * @param  type [input data]
 */
#define etool_linkQueue_head(queue, value, type) \
do { \
	if ((queue)->length > 0) { \
		value = *(type*)((queue)->front->next->data); \
	} \
} while(0)

/**
 * int etool_linkQueue_peer_head(etool_linkQueue *queue, void *value);
 * 获取队尾元素,O(1)
 * @param  queue [description]
 * @param  value [description]
 * @param  type [input data]
 */
#define etool_linkQueue_peer_head(queue, value, type) \
do { \
	if ((queue)->length > 0) { \
		value = *(type*)((queue)->rear->data); \
	} \
} while(0)

/**
 * int etool_linkQueue_enter(etool_linkQueue *queue, const void *value);
 * 进入队列,O(1)
 * @param  queue [description]
 * @param  value [description]
 * @param  type [input data]
 */
#define etool_linkQueue_enter(queue, value, type) \
do { \
	struct _etool_linkNode *node = (struct _etool_linkNode*)malloc(sizeof(struct _etool_linkNode) + sizeof(type)); \
	if (node != 0) { \
		node->data = (unsigned char*)node + sizeof(struct _etool_linkNode); \
		*(type*)(node->data) = value; \
		node->next = 0; \
		(queue)->rear->next = node; \
		(queue)->rear = node; \
		(queue)->length++; \
	} \
} while(0)

/**
 * int etool_linkQueue_peer_enter(etool_linkQueue *queue, const void *value);
 * 进入队列(从队头进入),O(1)
 * @param  queue [description]
 * @param  value [description]
 * @param  type [input data]
 */
#define etool_linkQueue_peer_enter(queue, value, type) \
do { \
	struct _etool_linkNode *node = (struct _etool_linkNode*)malloc(sizeof(struct _etool_linkNode) + sizeof(type)); \
	if (node != 0) { \
		node->data = (unsigned char*)node + sizeof(struct _etool_linkNode); \
		*(type*)(node->data) = value; \
		node->next = (queue)->front->next; \
		(queue)->front->next = node; \
		(queue)->length++; \
	} \
} while(0)

/**
 * int etool_linkQueue_exit(etool_linkQueue *queue, void *value);
 * 退出队列,O(1)
 * @param  queue [description]
 * @param  value [description]
 * @param  type [output data]
 */
#define etool_linkQueue_exit(queue, value, type) \
do { \
	if ((queue)->length > 0) { \
		struct _etool_linkNode *node = (queue)->front->next; \
		value = *(type*)(node->data); \
		(queue)->front->next = node->next; \
		(queue)->length--; \
		free(node); \
	} \
} while(0)

/**
 * int etool_linkQueue_peer_exit(etool_linkQueue *queue, void *value);
 * 退出队列(从队尾退出),O(1)
 * @param  queue [description]
 * @param  value [description]
 * @param  type [output data]
 */
#define etool_linkQueue_peer_exit(queue, value, type) \
do { \
	if ((queue)->length > 0) { \
		unsigned int n; \
		struct _etool_linkNode *node = (queue)->front->next; \
		for (n = 2; n < (queue)->length; n++) { \
			node = node->next; \
		} \
		value = *(type*)((queue)->rear->data); \
		free((queue)->rear); \
		node->next = 0; \
		(queue)->rear = node; \
		(queue)->length--; \
	} \
} while(0)

/**
 * etool_linkQueueIterator* etool_linkQueueIterator_init(etool_linkQueue *queue);
 * 遍历迭代器
 * @param  queue [description]
 * @param  block [description]
 * @param  element [description]
 * @param  type [description]
 */
#define etool_linkQueue_iterator(queue, block, element, type) \
do { \
	type *element; \
	struct _etool_linkNode *node = (queue)->front->next; \
	while (node != 0) { \
		element = (type*)(node->data); \
		block \
		node = node->next; \
	} \
} while(0)

#endif //ETOOL_TYPE_LINKQUEUE