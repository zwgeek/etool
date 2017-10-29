/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 基于块分配的内存(管理)模块
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_POOL_MEMORY
#define ETOOL_POOL_MEMORY

#include <stdlib.h>

#define ETOOL_MODE_CREATE	0
#define ETOOL_MODE_INIT		1
#define ETOOL_MEMORY_EXTEND(memory) \
unsigned char *_data = malloc(memory->typeSize * memory->size * 2 + sizeof(void*) * memory->size * 2); \
unsigned char **_freeAddr = (unsigned char**)(_data + memory->typeSize * memory->size * 2); \
int offset = 0; \
for (int n = 0; n < memory->size; n++) { \
	_data[offset] = memory->data[offset]; \
	offset++; \
	for (int m = 1; m < memory->typeSize; m++) { \
		_data[offset] = memory->data[offset]; \
		offset++; \
	} \
	_freeAddr[n] = memory->freeAddr[n]; \
} \
free(memory->data); \
memory->data = _data; \
memory->freeAddr = _freeAddr \

typedef struct _etool_memory {
	unsigned char *data;
	unsigned char **freeAddr;
	unsigned int typeSize;
	unsigned int size;
	unsigned int length;
	unsigned int mode;
} etool_memory;

/**
 * 创建memory (动态存储表示)
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return          [实体]
 */
etool_memory* etool_memory_create(unsigned int typeSize, unsigned int size);

/**
 * 销毁memory(动态存储表示)
 * @param  memory [not null]
 * @return      [error code]
 */
void etool_memory_destroy(etool_memory *memory);

/**
 * 创建一个符合要求的memory需要的字节数
 * @param  typeSize [description]
 * @param  size     [description]
 * @return          [description]
 */
int etool_memory_size(unsigned int typeSize, unsigned int size);

/**
 * 初始化一个memory 并且将一个内存块设入memory模块(静态/动态存储表示),内存块由开发者创建销毁
 * @param  block     [description]
 * @param  typeSize [description]
 * @param  size     [description]
 * @return          [实体]
 */
etool_memory* etool_memory_init(void *block, unsigned int typeSize, unsigned int size);

/**
 * 清空memory
 * @param  memory [description]
 */
void etool_memory_clear(etool_memory *memory);

/**
 * 申请memory里一块特定元素
 * @param memory [not null]
 * @return      [元素指针]
 */
void* etool_memory_malloc(etool_memory *memory);

/**
 * 释放memory里一块特定元素
 * @param memory [not null]
 * @param  node [description]
 * @return        [description]
 */
int etool_memory_free(etool_memory *memory, void *node);

#endif //ETOOL_POOL_MEMORY