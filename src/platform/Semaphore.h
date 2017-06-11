/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 信号量 POSIX 无名
 */

#ifndef ETOOL_PLATFORM_SEMAPHORE
#define ETOOL_PLATFORM_SEMAPHORE

#if defined(_windows)
#include <windows.h>			
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
#include <sys/time.h>
#include <semaphore.h>
#endif

namespace etool {

struct SemaphoreInterior {
#if defined(_windows)
	HANDLE semaphore;
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	sem_t semaphore;
#endif
};

class CSemaphore
{
	CSemaphore(const CSemaphore&) {}
	CSemaphore& operator=(const CSemaphore&) { return *this; }
public:
	CSemaphore(int initNum = 1);
	~CSemaphore();

	void pend();
	bool trypend(long timeOut = 0);
	void post();

private:
	SemaphoreInterior m_interior;
};
} //etool
#endif //ETOOL_PLATFORM_SEMAPHOR
