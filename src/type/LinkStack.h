/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于链表方式的栈(不使用Memory模块)
 */

#ifndef ETOOL_TYPE_LINKSTACK
#define ETOOL_TYPE_LINKSTACK

#include <stdlib.h>

typedef struct _etool_linkStack {
	unsigned int length;
	struct _etool_linkNode *top;
} etool_linkStack;

#ifndef ETOOL_LINKNODE
#define ETOOL_LINKNODE
struct _etool_linkNode {
	unsigned char *data;
	struct _etool_linkNode *next;
};
#endif


/**
 * etool_linkStack* etool_linkStack_create(const unsigned int typeSize);
 * 创建stack (动态存储表示)
 * @param  typeSize [not null]
 */
#define etool_linkStack_init(stack) \
do { \
	etool_linkStack *stack = (etool_linkStack*)malloc(sizeof(etool_linkStack)); \
	if (stack == 0) { \
		(stack)->length = 0; \
		(stack)->top = 0; \
	} \
} while(0)

/**
 * void etool_linkStack_destroy(etool_linkStack *stack);
 * 销毁stack(动态存储表示)
 * @param  stack [not null]
 */
#define etool_linkStack_free(stack) \
do { \
	struct _etool_linkNode *node; \
	while ((stack)->top != 0) { \
		node = (stack)->top; \
		(stack)->top = node->next; \
		free(node); \
	} \
	free(stack); \
	stack = 0; \
} while(0)

/**
 * void etool_linkStack_clear(etool_linkStack *stack);
 * 清空stack
 * @param  stack [description]
 */
#define etool_linkStack_clear(stack) \
do { \
	struct _etool_linkNode *node; \
	while ((stack)->top != 0) { \
		node = (stack)->top; \
		(stack)->top = node->next; \
		free(node); \
	} \
	(stack)->length = 0; \
} while(0)

/**
 * int etool_linkStack_length(etool_linkStack *stack);
 * 获得stack的有效长度
 * @param  stack [description]
 */
#define etool_linkStack_length(stack) \
((stack)->length)

/**
 * int etool_linkStack_empty(etool_linkStack *stack);
 * stack是否为空
 * @param  stack [description]
 */
#define etool_linkStack_empty(stack) \
((stack)->length == 0)

/**
 * int etool_linkStack_head(etool_linkStack *stack, void *value);
 * 获取栈头元素,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @param  type [input data]
 */
#define etool_linkStack_head(stack, value, type) \
do { \
	if ((stack)->length > 0) { \
		struct _etool_linkNode *node = (stack)->top; \
		value = *(type*)(node->data); \
	} \
} while(0)

/**
 * int etool_linkStack_push(etool_linkStack *stack, const void *value);
 * stack压入,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @param  type [input data]
 */
#define etool_linkStack_push(stack, value, type) \
do { \
	struct _etool_linkNode *node = (struct _etool_linkNode*)malloc(sizeof(struct _etool_linkNode)); \
	if (node != 0) { \
		*(type*)(node->data) = value; \
		node->next = (stack)->top; \
		(stack)->top = node; \
		(stack)->length++; \
	} \
} while(0)

/**
 * int etool_linkStack_pop(etool_linkStack *stack, void *value);
 * stack弹出,O(1)
 * @param  stack [description]
 * @param  value [output data]
 * @param  type [output data]
 */
#define etool_linkStack_pop(stack, value, type) \
do { \
	if ((stack)->length > 0) { \
		struct _etool_linkNode *node = (stack)->top; \
		(stack)->top = node->next; \
		(stack)->length--; \
		value = *(type*)(node->data); \
		free(node); \
	} \
} while(0)

/**
 * etool_linkStackIterator* etool_linkStackIterator_init(etool_linkStack *stack);
 * 遍历迭代器
 * @param  stack [description]
 * @param  block [description]
 * @param  element [description]
 * @param  type [description]
 */
#define etool_linkStack_iterator(stack, block, element, type) \
do { \
	type *element; \
	struct _etool_linkNode *node = (stack)->top; \
	while (node != 0) { \
		element = (type*)(node->data); \
		block \
		node = node->next; \
	} \
} while(0)

#endif //ETOOL_TYPE_LINKSTACK
