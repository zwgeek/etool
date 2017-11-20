// /**
//  * Copyright 2017, PaPa.  All rights reserved.
//  * 日志
//  */

// #ifndef ETOOL_LOG
// #define ETOOL_LOG


// #include <stdio.h>
// #include <string.h>
// #if defined(_windows) || defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
// #endif


// enum etool_logLevel {
// 	VERBOSE = 0,
// 	DEBUG,
// 	INFO,
// 	WARN,
// 	ERROR
// };
// enum etool_logMode {
// 	COMMON = 0,		//普通
// 	LOOP			//双循环
// };


// /**
//  * 日志模块打开
//  * @param path  [not null]
//  * @param mode  [null/default 0]
//  * @param level [null/default VERBOSE]
//  * @return       [error code]
//  */
// int etool_log_open(const char *path, unsigned int level, unsigned int mode);
// /**
//  * 日志模块关闭
//  */
// void etool_log_close();
// /**
//  * 设置日志模块输出路径
//  * @param path [not null]
//  */
// void etool_log_path(const char *path);
// /**
//  * 设置日志模块等级
//  * @param level [null/default VERBOSE]
//  */
// void etool_log_level(unsigned int level);
// /**
//  * 设置日志模块输出模式
//  * @param mode [null/default 0]
//  */
// void etool_log_mode(unsigned int mode);
// /**
//  * 日志输出
//  * @param level [not null]
//  * @param fmt [not null]
//  */
// void etool_log_printf(enum etool_logLevel level, const char *fmt, ...);

// #endif //ETOOL_LOG
