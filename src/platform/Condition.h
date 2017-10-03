/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 条件变量
 */

#ifndef ETOOL_PLATFORM_CONDITION
#define ETOOL_PLATFORM_CONDITION

#include <stdlib.h>
#include "MutexEx.h"
#if defined(_windows)
#include <windows.h>				
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
#include <sys/time.h>
#include <pthread.h>			
#endif


typedef struct etool_conditionInterior
{
#if defined(_windows)
	//waiters must be eq the Semaphore count
	int waiters;
	HANDLE cond; 
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_t cond;
#endif
} *etool_condition;


int etool_condition_create(etool_condition *condition);
void etool_condition_destroy(etool_condition *condition);
void etool_condition_wait(etool_condition *condition, etool_mutexEx *mutex);
int etool_condition_trywait(etool_condition *condition, etool_mutexEx *mutex, long timeOut);
void etool_condition_signal(etool_condition *condition);
void etool_condition_broadcast(etool_condition *condition);

#endif //ETOOL_PLATFORM_CONDITION
