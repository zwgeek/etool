/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 互斥锁
 */

#ifndef ETOOL_PLATFORM_MUTEX
#define ETOOL_PLATFORM_MUTEX

#include <stdlib.h>
#if defined(_windows)
#include <windows.h>
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <pthread.h>		
#endif

#define MUTEX_NULL 0

typedef struct {
#if defined(_windows)
	CRITICAL_SECTION mutex;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_t mutex;
#endif
} etool_mutex;

/**
 * 创建
 * @param  mutex [not null]
 * @return       [error code]
 */
int etool_mutex_create(etool_mutex *mutex);
/**
 * 销毁
 * @param mutex [not null]
 */
void etool_mutex_destroy(etool_mutex *mutex);
/**
 * 锁
 * @param mutex [not null]
 */
void etool_mutex_lock(etool_mutex *mutex);
/**
 * 尝试锁
 * @param  mutex [not null]
 * @return       [error code]
 */
int etool_mutex_trylock(etool_mutex *mutex);
/**
 * 解锁
 * @param mutex [not null]
 */
void etool_mutex_unlock(etool_mutex *mutex);

#endif //ETOOL_PLATFORM_MUTEX
