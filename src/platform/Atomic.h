/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 原子计数器
 */

#ifndef ETOOL_PLATFORM_ATOMIC
#define ETOOL_PLATFORM_ATOMIC

#include <stdlib.h>
#if defined(_windows)
#include <windows.h>
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#endif

typedef struct _etool_atomic {
#if defined(_windows)
	LONG volatile count;
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	int count;
#endif
} etool_atomic;

/**
 * 创建
 * @return       [实体]
 */
etool_atomic* etool_atomic_create(const int count);

/**
 * 销毁
 * @param atomic [not null]
 */
void etool_atomic_destroy(etool_atomic *atomic);

/**
 * 自增
 * @param atomic [not null]
 */
int etool_atomic_inc(etool_atomic *atomic);

/**
 * 自减
 * @param atomic [not null]
 */
int etool_atomic_dec(etool_atomic *atomic);

/**
 * 增
 * @param atomic [not null]
 */
int etool_atomic_add(etool_atomic *atomic, const int count);

/**
 * 减
 * @param atomic [not null]
 */
int etool_atomic_sub(etool_atomic *atomic, const int count);

/**
 * 或运算(位)
 * @param atomic [not null]
 */
int etool_atomic_or(etool_atomic *atomic, const int count);

/**
 * 与运算(位)
 * @param atomic [not null]
 */
int etool_atomic_and(etool_atomic *atomic, const int count);

/**
 * 异或运算(位)
 * @param atomic [not null]
 */
int etool_atomic_xor(etool_atomic *atomic, const int count);

#endif //ETOOL_PLATFORM_ATOMIC
