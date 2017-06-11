/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 递归锁扩展, 支持条件变量使用
 */

#ifndef ETOOL_PLATFORM_MUTEXEX
#define ETOOL_PLATFORM_MUTEXEX

#if defined(_windows)
#include <windows.h>		
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <pthread.h>	
#endif
 
namespace etool {

class CCondition;
struct MutexExInterior {
#if defined(_windows)
	HANDLE mutex;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_t mutex;
#endif
};

class CMutexEx
{
	friend class CCondition;
	CMutexEx(const CMutexEx&) {}
	CMutexEx& operator=(const CMutexEx&) { return *this; }
public:
	CMutexEx();
	~CMutexEx();

	void lock();
	bool trylock();
	void unlock();
private: 
	MutexExInterior m_interior;
};
} //etool
#endif //ETOOL_PLATFORM_MUTEXEX