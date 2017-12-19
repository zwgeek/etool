/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于链表方式的栈(不使用Memory模块)
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_LINKSTACK
#define ETOOL_TYPE_LINKSTACK

#include <stdlib.h>

typedef struct _etool_linkStack {
	unsigned int typeSize;
	unsigned int length;
	struct _etool_linkNode *top;
} etool_linkStack;

struct _etool_linkNode {
	unsigned char *data;
	struct _etool_linkNode *next;
};

typedef struct _etool_linkStackIterator {
	unsigned char *data;
	struct _etool_linkNode *next;
} etool_linkStackIterator;


/**
 * 创建stack (动态存储表示)
 * @param  typeSize [not null]
 * @return      [实体]
 */
etool_linkStack* etool_linkStack_create(const unsigned int typeSize);

/**
 * 销毁stack(动态存储表示)
 * @param  stack [not null]
 * @return      [error code]
 */
void etool_linkStack_destroy(etool_linkStack *stack);

/**
 * 清空stack
 * @param  stack [description]
 * @return      [description]
 */
void etool_linkStack_clear(etool_linkStack *stack);

/**
 * 获得stack的有效长度
 * @param  stack [description]
 * @return      [description]
 */
int etool_linkStack_length(etool_linkStack *stack);

/**
 * stack是否为空
 * @param  stack [description]
 * @return      [bool code]
 */
int etool_linkStack_empty(etool_linkStack *stack);

/**
 * 获取栈头元素,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_linkStack_head(etool_linkStack *stack, void *value);

/**
 * stack压入,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_linkStack_push(etool_linkStack *stack, const void *value);

/**
 * stack弹出,O(1)
 * @param  stack [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_linkStack_pop(etool_linkStack *stack, void *value);

/**
 * 创建迭代器
 * @param  stack [description]
 * @return         [description]
 */
etool_linkStackIterator* etool_linkStackIterator_init(etool_linkStack *stack);

/**
 * 遍历迭代器
 * @param  iterator [description]
 * @return          [description]
 */
int etool_linkStackIterator_next(etool_linkStackIterator *iterator);

#endif //ETOOL_TYPE_LINKSTACK
