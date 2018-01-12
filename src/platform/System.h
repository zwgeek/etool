/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 系统模块: 一些常用的工具使用
 * #define F_OK			//只判断是否存在
 * #define R_OK			//判断写入权限
 * #define W_OK			//判断读取权限
 * #define X_OK			//判断执行权限
 * #define EACCESS		//所指定的文件不符合所要求测试的权限
 * #define EROFS		//欲测试写入权限的文件存在于只读文件系统内
 * #define EFAULT		//参数pathname指针超出可存取内存空间
 * #define EINVAL		//参数mode不正确
 * #define ENAMETOOLONG	//参数pathname太长
 * #define ENOTDIR		//参数pathname为一目录
 * #define ENOMEM		//核心内存不足
 * #define ELOOP		//参数pathname有过多符号连接问题
 * #define EIO			//存取错误
 */

#ifndef ETOOL_PLATFORM_SYSTEM
#define ETOOL_PLATFORM_SYSTEM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#if defined(_windows)
#include <windows.h>
#include <io.h>	//判断文件夹
#include <direct.h>	//创建|删除文件夹
#endif
#if defined(_android) || defined(_linux)
#include <unistd.h>	//判断文件夹
#include <sys/types.h>//创建文件夹
#include <sys/stat.h>   //创建文件夹
#include <dirent.h>	//创建|删除文件夹
#endif
#if defined(_mac) || defined(_ios)
#include <sys/time.h>
#include <unistd.h>	//判断文件夹
#include <sys/types.h>//创建文件夹
#include <sys/stat.h>   //创建文件夹
#include <dirent.h>	//删除文件夹
#endif

// error code
// #define ETOOL_


/**
 * 时间戳
 * @return [s]
 */
time_t etool_os_time();

/**
 * 程序启动时的计时器
 * @return [ms(CLOCKS_PER_SEC)]
 */
clock_t etool_os_clock();

/**
 * 睡眠
 * @param milliseconds [not null]
 */
void etool_os_sleep(const unsigned long milliseconds);

/**
 * 判断文件夹是否存在
 * @param  path [not null]
 * @return      [error code]
 */
int etool_dir_exist(const char *path);

/**
 * 创建文件夹
 * @param  path [not null]
 * @return      [error code]
 */
int etool_dir_create(const char *path);

/**
 * 删除文件夹
 * @param  path [not null]
 * @return      [error code]
 */
int etool_dir_delete(const char *path);

#endif //ETOOL_PLATFORM_SYSTEM
