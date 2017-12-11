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

#ifndef ETOOL_SYSTEM
#define ETOOL_SYSTEM

// error code
// #define ETOOL_

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

#endif //ETOOL_SYSTEM
