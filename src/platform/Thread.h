/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 线程
 */

#ifndef ETOOL_PLATFORM_THREAD
#define ETOOL_PLATFORM_THREAD

#include <stdlib.h>
#if defined(_windows)
#include <windows.h>
#include <process.h> 
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
#include <pthread.h>
#endif


typedef void etool_threadPorc();
typedef struct etool_threadInterior {
	int         loop;
#if defined(_windows)
	HANDLE thread;
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_t thread;
#endif
} *etool_thread;

unsigned long etool_thread_getCurrentID();
int etool_thread_create(etool_thread *thread);
void etool_thread_destroy(etool_thread *thread);
int etool_thread_loop(etool_thread *thread);
void etool_thread_start(etool_thread *thread, etool_threadPorc *proc);
void etool_thread_end(etool_thread *thread);
int etool_thread_cancel(etool_thread *thread);
void etool_thread_terminate(etool_thread *thread);

#if defined(_windows)
	unsigned int __stdcall g_threadPorc(void *proc) {((etool_threadPorc*)proc)(); return 0;}
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	void* g_threadPorc(void *proc) {((etool_threadPorc*)proc)(); return 0;}
#endif

#endif //ETOOL_PLATFORM_THREAD
