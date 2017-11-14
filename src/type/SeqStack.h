/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 基于数组方式的栈
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_SEQSTACK
#define ETOOL_TYPE_SEQSTACK

#include <stdlib.h>

#define ETOOL_MODE_CREATE 0
#define ETOOL_MODE_INIT   1
#define ETOOL_SEQSTACK_EXTEND(stack) \
unsigned char *_data = malloc(stack->typeSize * stack->size * 2); \
for (int n = 0; n < stack->typeSize * stack->size; n++) { \
	_data[n] = stack->data[n]; \
} \
free(stack->data); \
stack->data = _data \

typedef struct {
	unsigned char *data;
	unsigned int typeSize;
	unsigned int size;
	unsigned int top;
	unsigned int mode;
} etool_seqStack;

/**
 * 创建stack (动态存储表示)
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return      [实体]
 */
etool_seqStack* etool_seqStack_create(const unsigned int typeSize, const unsigned int size);

/**
 * 销毁stack(动态存储表示)
 * @param  stack [not null]
 * @return      [error code]
 */
void etool_seqStack_destroy(etool_seqStack *stack);

/**
 * 创建一个符合要求的stack需要的字节数
 * @param  typeSize [description]
 * @param  size     [description]
 * @return          [description]
 */
int etool_seqStack_size(const unsigned int typeSize, const unsigned int size);

/**
 * 初始化一个stack, 并且将一个数据源设入stack(静态/动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return      [实体]
 */
etool_seqStack* etool_seqStack_init(void *block, const unsigned int typeSize, const unsigned int size);

/**
 * 清空stack
 * @param  stack [description]
 * @return      [description]
 */
void etool_seqStack_clear(etool_seqStack *stack);

/**
 * 获得stack的有效长度
 * @param  stack [description]
 * @return      [description]
 */
int etool_seqStack_length(etool_seqStack *stack);

/**
 * stack是否为空
 * @param  stack [description]
 * @return      [bool code]
 */
int etool_seqStack_empty(etool_seqStack *stack);

/**
 * stack是否已满
 * @param  stack [description]
 * @return      [bool code]
 */
int etool_seqStack_full(etool_seqStack *stack);

/**
 * 压入,O(1)
 * @param  stack [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_seqStack_push(etool_seqStack *stack, void *value);

/**
 * 弹出,O(1)
 * @param  stack [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_seqStack_pop(etool_seqStack *stack, void *value);

#endif //ETOOL_TYPE_SEQSTACK
