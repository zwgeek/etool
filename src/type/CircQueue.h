/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于循环数组方式的(支持双端队列)队列
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_CIRCQUEUE
#define ETOOL_TYPE_CIRCQUEUE

#include <stdlib.h>

#define ETOOL_CIRCQUEUE_EXTEND(queue, type) \
unsigned int n; \
type *_data = (type*)malloc((queue)->size << 1 * sizeof(type)); \
for (n = 0; n <= (queue)->rear; n++) { \
	_data[(queue)->size + n] = ((type*)(queue)->data)[n]; \
} \
for (; n < (queue)->size; n++) { \
	_data[n] = ((type*)(queue)->data)[n]; \
} \
free((queue)->data); \
(queue)->data = (unsigned char*)_data; \
(queue)->rear = (queue)->size + (queue)->rear; \
(queue)->size = (queue)->size << 1; \
(queue)->limit = (queue)->size - 1

typedef struct _etool_circQueue {
	unsigned char *data;
	unsigned int front;
	unsigned int rear;
	unsigned int size;
	unsigned int limit;
} etool_circQueue;


/**
 * etool_circQueue* etool_circQueue_init(etool_circQueue *queue, const unsigned int size);
 * 初始化一个queue, 并且将一个数据源queue设入(静态/动态存储表示),容器数据由开发者创建销毁
 * @param  queue     [not null]
 * @param  volume   [not null]
 * @param  type [description]
 */
#define etool_circQueue_init(queue, volume, type) \
do { \
	queue = (etool_circQueue*)malloc(sizeof(etool_circQueue)); \
	if (queue != 0) { \
		(queue)->data = (unsigned char*)malloc(volume * sizeof(type)); \
		if ((queue)->data != 0) { \
			(queue)->front = 0; \
			(queue)->rear = 0; \
			(queue)->size = volume; \
			(queue)->limit = volume - 1; \
		} else { \
			free(queue); \
			queue = 0; \
		} \
	} \
} while(0)

/**
 * void etool_circQueue_free(etool_circQueue *queue);
 * 释放queue (动态存储表示)
 * @param  queue [not null]
 */
#define etool_circQueue_free(queue) \
do { \
	free((queue)->data); \
	free(queue); \
	queue = 0; \
} while(0)

/**
 * void etool_circQueue_clear(etool_circQueue *queue);
 * 清空queue
 * @param  queue [description]
 */
#define etool_circQueue_clear(queue) \
do { \
	(queue)->front = 0; \
	(queue)->rear = 0; \
} while(0)

/**
 * int etool_circQueue_length(etool_circQueue *queue);
 * 获得queue的有效长度
 * @param  queue [description]
 */
#define etool_circQueue_length(queue) \
((queue)->rear >= (queue)->front ? ((queue)->rear - (queue)->front) : ((queue)->rear - (queue)->front + (queue)->size))


/**
 * int etool_circQueue_empty(etool_circQueue *queue);
 * queue是否为空
 * @param  queue [description]
 */
#define etool_circQueue_empty(queue) \
((queue)->rear == (queue)->front)

/**
 * int etool_circQueue_full(etool_circQueue *queue);
 * queue是否已满
 * @param  queue [description]
 */
#define etool_circQueue_full(queue) \
(((queue)->rear == (queue)->limit ? 0 : (queue)->rear + 1) == (queue)->front)

/**
 * int etool_circQueue_head(etool_circQueue *queue, void *value);
 * 获取队头元素,O(1)
 * @param  queue [description]
 * @param  value [output data, not null]
 * @param  type [description]
 */
#define etool_circQueue_head(queue, value, type) \
do { \
	if ((queue)->rear == (queue)->front) { \
		value = ((type*)((queue)->data))[(queue)->front == (queue)->limit ? 0 : (queue)->front + 1]; \
	} \
} while(0)

/**
 * int etool_circQueue_peer_head(etool_circQueue *queue, void *value)
 * 获取队尾元素,O(1)
 * @param  queue [description]
 * @param  value [input data]
 * @param  type [description]
 */
#define etool_circQueue_peer_head(queue, value, type) \
do { \
	if ((queue)->rear == (queue)->front) { \
		value = ((type*)((queue)->data))[(queue)->rear]; \
	} \
} while(0)

/**
 * int etool_circQueue_enter(etool_circQueue *queue, const void *value);
 * 进入队列,O(1)
 * @param  queue [description]
 * @param  value [input data]
 * @param  type [description]
 */
#define etool_circQueue_enter(queue, value, type) \
do { \
	(queue)->rear = (queue)->rear == (queue)->limit ? 0 : (queue)->rear + 1; \
	((type*)((queue)->data))[(queue)->rear] = value; \
	if ((queue)->rear == (queue)->front) { ETOOL_CIRCQUEUE_EXTEND(queue, type); } \
} while(0)

/**
 * int etool_circQueue_peer_enter(etool_circQueue *queue, const void *value);
 * 进入队列(从队头进入),O(1)
 * @param  queue [description]
 * @param  value [input data]
 * @param  type [description]
 */
#define etool_circQueue_peer_enter(queue, value, type) \
do { \
	((type*)((queue)->data))[(queue)->front] = value; \
	(queue)->front = (queue)->front == 0 ? (queue)->limit : (queue)->front - 1; \
	if ((queue)->front == (queue)->rear) { ETOOL_CIRCQUEUE_EXTEND(queue, type); } \
} while(0)

/**
 * int etool_circQueue_exit(etool_circQueue *queue, void *value);
 * 退出队列,O(1)
 * @param  queue [description]
 * @param  value [output data]
 * @param  type [description]
 */
#define etool_circQueue_exit(queue, value, type) \
do { \
	(queue)->front = (queue)->front == (queue)->limit ? 0 : (queue)->front + 1; \
	value = ((type*)((queue)->data))[(queue)->front]; \
} while(0)

/**
 * int etool_circQueue_peer_exit(etool_circQueue *queue, void *value);
 * 退出队列(从队尾退出),O(1)
 * @param  queue [description]
 * @param  value [output data]
 * @param  type [description]
 */
#define etool_circQueue_peer_exit(queue, value, type) \
do { \
	value = ((type*)((queue)->data))[(queue)->rear]; \
	(queue)->rear = (queue)->rear == 0 ? (queue)->limit : (queue)->rear - 1; \
} while(0)

/**
 * etool_circQueueIterator* etool_circQueue_iterator(etool_circQueue *queue);
 * 遍历迭代器
 * @param  queue [description]
 */
#define etool_circQueue_iterator(queue, block, element, type) \
do { \
	type *element; \
	unsigned int num = (queue)->front; \
	while (num != (queue)->rear) { \
		num = num == (queue)->limit ? 0 : num + 1; \
		element = (type*)((queue)->data) + num; \
		block \
	} \
} while(0)

#endif //ETOOL_TYPE_CIRCQUEUE