/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 日志
 */

#ifndef ETOOL_LOG
#define ETOOL_LOG

#define VERBOSE(fmt, ...) etool_log_printf(g_log, ETOOL_LOG_VERBOSE, "__FILE__:__FUNCTION__:%05d--verbose: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define DEBUG(fmt, ...)   etool_log_printf(g_log, ETOOL_LOG_DEBUG, "__FILE__:__FUNCTION__:%05d--debug: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define INFO(fmt, ...)    etool_log_printf(g_log, ETOOL_LOG_INFO, "__FILE__:__FUNCTION__:%05d--info: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define WARN(fmt, ...)    etool_log_printf(g_log, ETOOL_LOG_WARN, "__FILE__:__FUNCTION__:%05d--warn: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define ERR(fmt, ...)     etool_log_printf(g_log, ETOOL_LOG_ERR, "__FILE__:__FUNCTION__:%05d--err: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define FATAL(fmt, ...)   etool_log_printf(g_log, ETOOL_LOG_FATAL, "__FILE__:__FUNCTION__:%05d--fatal: "fmt"\n", __LINE__, ##__VA_ARGS__)

typedef enum _etool_logLevel {
	ETOOL_LOG_VERBOSE = 0,
	ETOOL_LOG_DEBUG,
	ETOOL_LOG_INFO,
	ETOOL_LOG_WARN,
	ETOOL_LOG_ERR,
	ETOOL_LOG_FATAL
} etool_logLevel;

typedef struct _etool_log etool_log;

/**
 * 日志模块打开
 * @param path  [not null]
 * @param mode  [null/default 0]
 * @param level [null/default VERBOSE]
 * @return      [error code]
 */
etool_log* etool_log_create(const char *path, const etool_logLevel level);

/**
 * 日志模块关闭
 */
void etool_log_destroy(etool_log *log);

/**
 * 设置日志模块输出路径
 * @param log  [not null]
 * @param path [not null]
 * @return     [error code]
 */
int etool_log_path(etool_log *log, const char *path);

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
void etool_log_printf(etool_log *log, const etool_logLevel level, const char *fmt, ...);

/**
 * 日志输出
 * @param log [not null]
 * @param level [not null]
 * @param fmt [not null]
 */
void etool_log_async_printf(etool_log *log, const etool_logLevel level, const char *fmt, ...);

//声明一个log,跟宏搭配使用,建议这种用法
extern etool_log *g_log;

#endif //ETOOL_LOG
