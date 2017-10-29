/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 递归锁
 */

#ifndef ETOOL_PLATFORM_RECURSIVEMUTEX
#define ETOOL_PLATFORM_RECURSIVEMUTEX

#include <stdlib.h>
#if defined(_windows)
#include <windows.h>	
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <pthread.h>		
#endif

#define RECURSIVEMUTEX_NULL 0

typedef struct _etool_recursiveMutex {
#if defined(_windows)
	CRITICAL_SECTION  mutex;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_t mutex;
#endif
} etool_recursiveMutex;

/**
 * 创建
 * @return       [实体]
 */
etool_recursiveMutex* etool_recursiveMutex_create();

/**
 * 装载
 * @param mutex [not null]
 */
void etool_recursiveMutex_load(etool_recursiveMutex *mutex);

/**
 * 卸载
 * @param mutex [not null]
 */
void etool_recursiveMutex_unload(etool_recursiveMutex *mutex);

/**
 * 销毁
 * @param mutex [not null]
 */
void etool_recursiveMutex_destroy(etool_recursiveMutex *mutex);

/**
 * 锁
 * @param mutex [not null]
 */
void etool_recursiveMutex_lock(etool_recursiveMutex *mutex);

/**
 * 尝试锁
 * @param  mutex [not null]
 * @return       [error code]
 */
int etool_recursiveMutex_trylock(etool_recursiveMutex *mutex);

/**
 * 解锁
 * @param mutex [not null]
 */
void etool_recursiveMutex_unlock(etool_recursiveMutex *mutex);

#endif //ETOOL_PLATFORM_RECURSIVEMUTEX
