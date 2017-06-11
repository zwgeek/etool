/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 互斥锁
 */

#ifndef ETOOL_PLATFORM_MUTEX
#define ETOOL_PLATFORM_MUTEX

#if defined(_windows)
#include <windows.h>
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <pthread.h>		
#endif

namespace etool {

struct MutexInterior
{
#if defined(_windows)
	CRITICAL_SECTION mutex;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_t mutex;
#endif
};

class CMutex
{
	CMutex(const CMutex&) {}
	CMutex& operator=(const CMutex&) { return *this; }
public:
	CMutex();
	~CMutex();

	void lock();
	bool trylock();
	void unlock();
private: 
	MutexInterior m_interior;
};
} //etool
#endif //ETOOL_PLATFORM_MUTEX
