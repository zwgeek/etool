/**
 * Copyright 2017, PaPa.  All rights reserved.
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

typedef void etool_threadPorc(void *param);
typedef struct _etool_thread {
	int loop;
#if defined(_windows)
	HANDLE thread;
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_t thread;
#endif
} etool_thread;

struct _etool_threadAttr
{
	etool_threadPorc *porc;
	void *param;
};

/**
 * 获取线程ID
 * @return [ID]
 */
unsigned long etool_thread_getCurrentID();

/**
 * 创建线程
 * @return        [error code]
 */
etool_thread* etool_thread_create();

/**
 * 装载
 * @param thread [not null]
 */
void etool_thread_load(etool_thread *thread);

/**
 * 卸载
 * @param thread [not null]
 */
void etool_thread_unload(etool_thread *thread);

/**
 * 删除线程
 * @param thread [not null]
 */
void etool_thread_destroy(etool_thread *thread);

/**
 * 获取当前线程运行标志(循环时一定要加上这个判断)
 * @param  thread [not null]
 * @return        [flag]
 */
int etool_thread_loop(etool_thread *thread);

/**
 * 线程开始运行
 * @param thread [not null]
 * @param proc   [not null]
 * @param param  [not null]
 */
void etool_thread_start(etool_thread *thread, etool_threadPorc *proc, void *param);

/**
 * 线程结束运行(阻塞)
 * @param thread [not null]
 */
void etool_thread_end(etool_thread *thread);

/**
 * 线程取消运行(非阻塞)
 * @param thread [not null]
 */
int etool_thread_cancel(etool_thread *thread);

/**
 * 线程中断运行(非阻塞)
 * @param thread [not null]
 */
void etool_thread_terminate(etool_thread *thread);

#endif //ETOOL_PLATFORM_THREAD
