/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 系统类: 一些常用的工具使用
 */

#ifndef ETOOL_PLATFORM_SYSTEM
#define ETOOL_PLATFORM_SYSTEM

#include <stdio.h>
#include <stdlib.h>
//#include <string>
#if defined(_windows)
#include <windows.h>
#include <io.h>	//判断文件夹
#include <direct.h>	//创建|删除文件夹
#endif
#if defined(_android) || defined(_linux)
#include <system.h>
#include <unistd.h>	//文件夹操作
#include <dirent.h>	//创建|删除文件夹
#endif
#if defined(_mac) || defined(_ios)
#include <sys/time.h>
#include <unistd.h>	//文件夹操作
#include <dirent.h>	//创建|删除文件夹
#endif


// struct SystemInterior;

void etool_system_sleep(unsigned long milliseconds);
// void etool_system_mkdir(const char *filename);
// void etool_system_rmdir(const char *filename);

#endif //ETOOL_PLATFORM_SYSTEM
