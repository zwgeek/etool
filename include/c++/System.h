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
namespace etool {

class CSystem
{
private:
	CSystem() {}
	CSystem(const CSystem &system) {}
	~CSystem() {}
	CSystem& operator=(const CSystem &semaphore) {}

public:
	inline static void sleep(const unsigned long milliseconds = 1) { etool_os_sleep(milliseconds); }
	inline static int existDir(const char *path) { return etool_dir_exist(path); }
	inline static int createDir(const char *path) { return etool_dir_create(path); }
	inline static int deleteDir(const char *path) { return etool_dir_delete(path); }
};
} //etool
#endif //ETOOL_SEMAPHOR