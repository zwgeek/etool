/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 递归锁
 */

#ifndef ETOOL_PLATFORM_RECURSIVEMUTEX
#define ETOOL_PLATFORM_RECURSIVEMUTEX

#if defined(_windows)
#include <windows.h>	
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <pthread.h>		
#endif

namespace etool {

struct RecursiveMutexInterior {
#if defined(_windows)
	CRITICAL_SECTION  mutex;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_t mutex;
#endif
};

class CRecursiveMutex
{
	CRecursiveMutex(const CRecursiveMutex&) {}
	CRecursiveMutex& operator=(const CRecursiveMutex&) { return *this; }
public:
	CRecursiveMutex();
	~CRecursiveMutex();

	void lock();
	bool trylock();
	void unlock();
private:
	RecursiveMutexInterior m_interior;
};
} //etool
#endif //ETOOL_PLATFORM_RECURSIVEMUTEX
