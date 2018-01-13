/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于线程的线程池(管理)模块
 */

#ifndef ETOOL_POOL_EXECUTOR
#define ETOOL_POOL_EXECUTOR

#include <stdlib.h>
#include "../type/CircQueue.h"
#include "../platform/Mutex.h"
#include "../platform/Condition.h"
#include "../platform/Thread.h"
#include "../platform/System.h"

#define ETOOL_MAX_TICK 8
#define ETOOL_WORK_QUEUE_SIZE 20
#define ETOOL_TICK_TIME 10000

typedef void etool_workProc(void *param);
typedef struct _etool_executor {
	struct _etool_worker **workers;
	struct _etool_thread thread;
	unsigned int minCount;
	unsigned int maxCount;
} etool_executor;

struct _etool_worker {
	struct _etool_circQueue *queue;
	struct _etool_thread thread;
	struct _etool_mutexEx mutex;
	struct _etool_condition condition;
	unsigned short tick;
};


/**
 * 创建线程池
 * @param  minCount [description]
 * @param  maxCount [description]
 * @return          [description]
 */
etool_executor* etool_executor_create(unsigned int minCount, unsigned int maxCount);

/**
 * 销毁
 * @param executor [description]
 */
void etool_executor_destroy(etool_executor *executor);

/**
 * 加入工作
 * @param executor [description]
 * @param  work  [description]
 * @param  param [description]
 * @param  index [大于:随机选择一个线程体]
 * @return       [description]
 */
void etool_executor_work(etool_executor *executor, etool_workProc *work, void *param, const unsigned int index);

#endif //ETOOL_POOL_EXECUTOR
