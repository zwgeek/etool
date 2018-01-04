/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于块分配的内存(管理)模块
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_POOL_MEMORY
#define ETOOL_POOL_MEMORY

#include <stdlib.h>

#define ETOOL_MEMORY_EXTEND(memory) \
int n, size = memory->size / memory->count * (memory->count + 1); \
unsigned char *_data = malloc(memory->typeSize * memory->size / memory->count); \
if (_data == 0) {return 0; } \
unsigned char **_freeAddr = malloc(sizeof(void*) * (size + memory->count + 1)); \
if (_freeAddr == 0) { free(_data); return 0; } \
for (n = 0; n < memory->size; n++) { \
	_freeAddr[n] = memory->freeAddr[n]; \
} \
for (n = 0; n < memory->count; n++) { \
	_freeAddr[size + n] = memory->freeAddr[memory->size + n]; \
} \
_freeAddr[size + memory->count] = _data; \
for (n = 0; n < (memory->size / memory->count); n++) { \
	_freeAddr[memory->size + n] = _data + n * memory->typeSize; \
} \
free(memory->freeAddr); \
memory->freeAddr = _freeAddr; \
memory->size = size; \
memory->count++ \

typedef struct _etool_memory {
	unsigned char **freeAddr;
	unsigned int typeSize;
	unsigned int size;
	unsigned int length;
	unsigned int count;
} etool_memory;

/**
 * 创建memory (动态存储表示)
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return          [实体]
 */
etool_memory* etool_memory_create(const unsigned int typeSize, const unsigned int size);

/**
 * 销毁memory(动态存储表示)
 * @param  memory [not null]
 * @return      [error code]
 */
void etool_memory_destroy(etool_memory *memory);

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