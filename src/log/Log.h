/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 日志
 */

#ifndef ETOOL_LOG
#define ETOOL_LOG

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Stdout.h"
#include "../type/CircQueue.h"
#include "../platform/Mutex.h"
#include "../platform/Condition.h"
#include "../platform/Thread.h"

#define ETOOL_LOG_MSG_SIZE 50
#define ETOOL_LOG_QUEUE_SIZE 50

typedef enum _etool_logLevel {
	VERBOSE = 0,
	DEBUG,
	INFO,
	WARN,
	ERR,
	FATAL
} etool_logLevel;

typedef struct _etool_log {
	FILE *file;
	char path[128];
	enum _etool_logLevel level;
	struct _etool_circQueue *queue;
	struct _etool_mutexEx mutex;
	struct _etool_condition condition;
	struct _etool_thread thread;
} etool_log;

/**
 * 日志模块打开
 * @param path  [not null]
 * @param mode  [null/default 0]
 * @param level [null/default VERBOSE]
 * @return       [error code]
 */
etool_log* etool_log_create(const char *path, const etool_logLevel level);

/**
 * 日志模块关闭
 */
void etool_log_destroy();

/**
 * 设置日志模块输出路径
 * @param log [not null]
 * @param path [not null]
 */
void etool_log_path(etool_log *log, const char *path);

/**
 * 设置日志模块等级
 * @param log [not null]
 * @param level [null/default VERBOSE]
 */
void etool_log_level(etool_log *log, const etool_logLevel level);

/**
 * 刷新日志模块
 * @param log [not null]
 */
void etool_log_flush(etool_log *log);

/**
 * 日志输出
 * @param log [not null]
 * @param level [not null]
 * @param fmt [not null]
 */
void etool_log_printf(etool_log *log, etool_logLevel level, const char *fmt, ...);

/**
 * 日志输出
 * @param log [not null]
 * @param level [not null]
 * @param fmt [not null]
 */
void etool_log_async_printf(etool_log *log, etool_logLevel level, const char *fmt, ...);

#endif //ETOOL_LOG
