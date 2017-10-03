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


typedef struct etool_recursiveMutexInterior
{
#if defined(_windows)
	CRITICAL_SECTION  mutex;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_t mutex;
#endif
} *etool_recursiveMutex;

int etool_recursiveMutex_create(etool_recursiveMutex *mutex);
void etool_recursiveMutex_destroy(etool_recursiveMutex *mutex);
void etool_recursiveMutex_lock(etool_recursiveMutex *mutex);
int etool_recursiveMutex_trylock(etool_recursiveMutex *mutex);
void etool_recursiveMutex_unlock(etool_recursiveMutex *mutex);

#endif //ETOOL_PLATFORM_RECURSIVEMUTEX
