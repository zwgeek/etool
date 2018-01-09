/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于数组方式的(支持双栈)栈
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_SEQSTACK
#define ETOOL_TYPE_SEQSTACK

#include <stdlib.h>

#define ETOOL_SEQSTACK_EXTEND(stack, type) \
int n, unitSize = (stack)->typeSize * ; \
type *_data = (type*)malloc((stack)->size << 1 * sizeof(type)); \
for (n = 0; n < (stack)->top; n++) { \
	_data[n] = ((type*)((stack)->data))[n]; \
} \
for (n = (stack)->size - 1; n >= (stack)->bottom; n--) { \
	_data[n] = ((type*)((stack)->data))[n]; \
} \
free((stack)->data); \
(stack)->data = (unsigned char*)_data; \
(stack)->bottom = (stack)->bottom + (stack)->size; \
(stack)->size = (stack)->size << 1

/**
 * 所有的数据结构里面都是当前指向的指针未被使用,只有bottom这一个特例(当前被使用)
 */
typedef struct _etool_seqStack {
	unsigned char *data;
	unsigned int top;
	unsigned int bottom;
	unsigned int size;
} etool_seqStack;

typedef struct _etool_seqStackIterator {
	unsigned char *data;
	struct _etool_seqStack *stack;
	unsigned int num;
} etool_seqStackIterator;


/**
 * etool_seqStack* etool_seqStack_init(void *block, const unsigned int typeSize, const unsigned int size)
 * 初始化一个stack, 并且将一个数据源设入stack(动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return      [实体]
 */
#define etool_seqStack_init(stack, volume, type) \
do { \
	stack = (etool_seqStack*)malloc(sizeof(etool_seqStack)); \
	if (stack != 0) { \
		(stack)->data = (unsigned char*)malloc(volume * sizeof(type)); \
		if ((stack)->data != 0) { \
			(stack)->size = size; \
			(stack)->top = 0; \
			(stack)->bottom = size; \
		} else { \
			free(stack); \
			stack = 0; \
		} \
	} \
} while(0)

/**
 * void etool_seqStack_destroy(etool_seqStack *stack);
 * 销毁stack(动态存储表示)
 * @param  stack [not null]
 * @return      [error code]
 */
#define etool_seqStack_free(stack) \
do { \
	free((stack)->data); \
	free(stack); \
	stack = 0; \
} while(0)

/**
 * void etool_seqStack_clear(etool_seqStack *stack);
 * 清空stack
 * @param  stack [description]
 * @return      [description]
 */
#define etool_seqStack_clear(stack) \
do { \
	(stack)->top = 0; \
	(stack)->bottom = (stack)->size; \
} while(0)

/**
 * int etool_seqStack_length(etool_seqStack *stack);
 * 获得stack的有效长度
 * @param  stack [description]
 * @return      [description]
 */
#define etool_seqStack_length(stack) \
((stack)->top)

/**
 * int etool_seqStack_other_length(etool_seqStack *stack);
 * 获得另一个stack的有效长度
 * @param  stack [description]
 * @return      [description]
 */
#define etool_seqStack_other_length(stack) \
((stack)->size - (stack)->bottom)

/**
 * int etool_seqStack_empty(etool_seqStack *stack);
 * stack是否为空
 * @param  stack [description]
 * @return      [bool code]
 */
#define etool_seqStack_empty(stack) \
((stack)->top == 0 && (stack)->bottom == (stack)->size)

/**
 * int etool_seqStack_full(etool_seqStack *stack);
 * stack是否已满
 * @param  stack [description]
 * @return      [bool code]
 */
#define etool_seqStack_full(stack) \
((stack)->top == (stack)->bottom)

/**
 * int etool_seqStack_head(etool_seqStack *stack, void *value);
 * 获取栈头元素,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @return      [description]
 */
#define etool_seqStack_head(stack, value, type) \
do { \
	if ((stack)->top > 0) { \
		value = ((type*)((stack)->data))[(stack)->top - 1]; \
	} \
} while(0)

/**
 * int etool_seqStack_other_head(etool_seqStack *stack, void *value);
 * 获取另一个栈头元素,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @return      [description]
 */
#define etool_seqStack_other_head(stack, value, type) \
do { \
	if ((stack)->bottom < (stack)->size) { \
		value = ((type*)((stack)->data))[(stack)->bottom]; \
	} \
} while(0)

/**
 * int etool_seqStack_push(etool_seqStack *stack, const void *value);
 * stack压入,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @return      [description]
 */
#define etool_seqStack_push(stack, value, type) \
do { \
	if ((stack)->top == (stack)->bottom) { \
		ETOOL_SEQSTACK_EXTEND(stack, type); \
	} \
	((type*)((stack)->data))[(stack)->top] = value; \
	(stack)->top++; \
} while(0)

/**
 * int etool_seqStack_other_push(etool_seqStack *stack, const void *value);
 * 另一个stack压入,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @return      [description]
 */
#define etool_seqStack_other_push(stack, value, type) \
do { \
	if (--(stack)->bottom < (stack)->top) { \
		ETOOL_SEQSTACK_EXTEND(stack, type); \
	} \
	((type*)((stack)->data))[(stack)->bottom] = value; \
} while(0)

/**
 * int etool_seqStack_pop(etool_seqStack *stack, void *value);
 * stack弹出,O(1)
 * @param  stack [description]
 * @param  value [output data]
 * @return      [description]
 */
#define etool_seqStack_pop(stack, value, type) \
do { \
	if ((stack)->top > 0) { \
		(stack)->top--; \
		value = ((type*)((stack)->data))[(stack)->top]; \
	} \
} while(0)

/**
 * int etool_seqStack_other_pop(etool_seqStack *stack, void *value);
 * 另一个stack弹出,O(1)
 * @param  stack [description]
 * @param  value [output data]
 * @return      [description]
 */
#define etool_seqStack_other_pop(stack, value, type) \
do { \
	if ((stack)->bottom < (stack)->size) { \
		value = ((type*)((stack)->data))[(stack)->bottom]; \
		(stack)->bottom++; \
	}
} while(0)

/**
 * etool_seqStackIterator* etool_seqStackIterator_init(etool_seqStack *stack);
 * 遍历迭代器
 * @param  iterator [description]
 * @return          [description]
 */
#define etool_seqStack_iterator(stack, block, element, type) \
do { \
	type *element; \
	unsigned int num; \
	for (num = 0; num < (stack)->top; num++) { \
		element = (type*)((stack)->data) + num; \
		block \
	} \
} while(0)

/**
 * etool_seqStackIterator* etool_seqStackIterator_other_init(etool_seqStack *stack);
 * 遍历另一个迭代器
 * @param  iterator [description]
 * @return          [description]
 */
#define etool_seqStack_other_iterator(stack, block, element, type) \
do { \
	type *element; \
	unsigned int num; \
	for (num = (stack)->size - 1; num >= (stack)->bottom; num--) { \
		element = (type*)((stack)->data) + num; \
		block \
	} \
} while(0)

#endif //ETOOL_TYPE_SEQSTACK
