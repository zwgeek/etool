/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于循环数组方式的(支持双队列)队列
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_CIRCQUEUE
#define ETOOL_TYPE_CIRCQUEUE

#include <stdlib.h>

#define ETOOL_MODE_CREATE	0
#define ETOOL_MODE_INIT		1
#define ETOOL_CIRCQUEUE_EXTEND(queue) \
unsigned char *_data = malloc(queue->typeSize * queue->size * 2); \
for (int n = 0; n < queue->typeSize * queue->size; n++) { \
	_data[n] = queue->data[(queue->front + n) % queue->size]; \
} \
free(queue->data); \
queue->data = _data; \
queue->front = 0; \
queue->rear = queue->size;\
queue->size = queue->size * 2 \

typedef struct _etool_circQueue {
	unsigned char *data;
	unsigned int typeSize;
	unsigned int front;
	unsigned int rear;
	unsigned int size;
	unsigned int mode;
} etool_circQueue;

/**
 * 创建queue (动态存储表示)
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return      [实体]
 */
etool_circQueue* etool_circQueue_create(const unsigned int typeSize, const unsigned int size);

/**
 * 销毁queue (动态存储表示)
 * @param  queue [not null]
 * @return      [error code]
 */
void etool_circQueue_destroy(etool_circQueue *queue);

/**
 * 创建一个符合要求的queue需要的字节数
 * @param  typeSize [description]
 * @param  size     [description]
 * @return          [description]
 */
int etool_circQueue_size(const unsigned int typeSize, const unsigned int size);

/**
 * 初始化一个queue, 并且将一个数据源设入queue(静态/动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return      [实体]
 */
etool_circQueue* etool_circQueue_init(void *block, const unsigned int typeSize, const unsigned int size);

/**
 * 清空queue
 * @param  queue [description]
 * @return      [description]
 */
void etool_circQueue_clear(etool_circQueue *queue);

/**
 * 获得queue的有效长度
 * @param  queue [description]
 * @return      [description]
 */
int etool_circQueue_length(etool_circQueue *queue);

/**
 * queue是否为空
 * @param  queue [description]
 * @return      [bool code]
 */
int etool_circQueue_empty(etool_circQueue *queue);

/**
 * queue是否已满
 * @param  queue [description]
 * @return      [bool code]
 */
int etool_circQueue_full(etool_circQueue *queue);

/**
 * 获取队头元素,O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_circQueue_get(etool_circQueue *queue, void *value);

/**
 * 获取队尾元素,O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_circQueue_other_get(etool_circQueue *queue, void *value);

/**
 * 进入队列,O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_circQueue_enter(etool_circQueue *queue, void *value);

/**
 * 进入队列(从队头进入),O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_circQueue_other_enter(etool_circQueue *queue, void *value);

/**
 * 退出队列,O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_circQueue_exit(etool_circQueue *queue, void *value);

/**
 * 退出队列(从队尾退出),O(1)
 * @param  queue [description]
 * @param  index [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_circQueue_other_exit(etool_circQueue *queue, void *value);

#endif //ETOOL_TYPE_CIRCQUEUE