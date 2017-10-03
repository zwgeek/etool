/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 信号量 POSIX 无名
 */

#ifndef ETOOL_PLATFORM_SEMAPHORE
#define ETOOL_PLATFORM_SEMAPHORE

#include <stdlib.h>
#if defined(_windows)
#include <windows.h>			
#endif
#if defined(_linux) || defined(_android)
#include <sys/time.h>
#include <semaphore.h>
#endif
#if defined(_mac) || defined(_ios)
#include <mach/semaphore.h>
#include <mach/task.h>
#include <mach/mach.h>
#endif


typedef struct etool_semaphoreInterior {
#if defined(_windows)
	HANDLE semaphore;
#endif
#if defined(_linux) || defined(_android)
	sem_t semaphore;
#endif
#if defined(_mac) || defined(_ios)
	semaphore_t semaphore;
#endif
} *etool_semaphore;

int etool_semaphore_create(etool_semaphore *semaphore, int initNum);
void etool_semaphore_destroy(etool_semaphore *semaphore);
void etool_semaphore_pend(etool_semaphore *semaphore);
int etool_semaphore_trypend(etool_semaphore *semaphore, long timeOut);
void etool_semaphore_post(etool_semaphore *semaphore);

#endif //ETOOL_PLATFORM_SEMAPHOR
