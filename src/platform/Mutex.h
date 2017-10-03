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


typedef struct etool_mutexInterior
{
#if defined(_windows)
	CRITICAL_SECTION mutex;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_t mutex;
#endif
} *etool_mutex;

int etool_mutex_create(etool_mutex *mutex);
void etool_mutex_destroy(etool_mutex *mutex);
void etool_mutex_lock(etool_mutex *mutex);
int etool_mutex_trylock(etool_mutex *mutex);
void etool_mutex_unlock(etool_mutex *mutex);

#endif //ETOOL_PLATFORM_MUTEX
