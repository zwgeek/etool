/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 读写锁(可递归)
 */

#ifndef ETOOL_PLATFORM_READWRITEMUTEX
#define ETOOL_PLATFORM_READWRITEMUTEX

#include <stdlib.h>
#include "Mutex.h"
#include "RecursiveMutex.h"


typedef struct etool_readWriteMutexInterior
{
	int                                               readCount;
	etool_mutex                              readMutex;
	etool_recursiveMutex               writeMutex;
} *etool_readWriteMutex;

int etool_readWriteMutex_create(etool_readWriteMutex *mutex);
void etool_readWriteMutex_destroy(etool_readWriteMutex *mutex);
void etool_readWriteMutex_lockRead(etool_readWriteMutex *mutex);
int etool_readWriteMutex_trylockRead(etool_readWriteMutex *mutex);
void etool_readWriteMutex_unlockRead(etool_readWriteMutex *mutex);
void etool_readWriteMutex_lockWrite(etool_readWriteMutex *mutex);
int etool_readWriteMutex_trylockWrite(etool_readWriteMutex *mutex);
void etool_readWriteMutex_unlockWrite(etool_readWriteMutex *mutex);

#endif //ETOOL_PLATFORM_READWRITEMUTEX
