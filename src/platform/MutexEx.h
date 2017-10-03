/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 递归锁扩展, 支持条件变量使用
 */

#ifndef ETOOL_PLATFORM_MUTEXEX
#define ETOOL_PLATFORM_MUTEXEX

#include <stdlib.h>
#if defined(_windows)
#include <windows.h>		
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <pthread.h>	
#endif


typedef struct etool_mutexExInterior
{
#if defined(_windows)
	HANDLE mutex;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_t mutex;
#endif
} *etool_mutexEx;

int etool_mutexEx_create(etool_mutexEx *mutex);
void etool_mutexEx_destroy(etool_mutexEx *mutex);
void etool_mutexEx_lock(etool_mutexEx *mutex);
int etool_mutexEx_trylock(etool_mutexEx *mutex);
void etool_mutexEx_unlock(etool_mutexEx *mutex);

#endif //ETOOL_PLATFORM_MUTEXEX