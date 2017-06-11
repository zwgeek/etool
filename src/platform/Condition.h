/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 条件变量
 */

#ifndef ETOOL_PLATFORM_CONDITION
#define ETOOL_PLATFORM_CONDITION

#include "MutexEx.h"
#if defined(_windows)
#include <windows.h>				
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
#include <sys/time.h>
#include <pthread.h>			
#endif
 
namespace etool {

struct ConditionInterior {
#if defined(_windows)
	//waiters must be eq the Semaphore count
	int waiters;
	HANDLE cond; 
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_t cond;
#endif
};

class CCondition
{
	CCondition(const CCondition&) {}
	CCondition& operator=(const CCondition&) { return *this; }

public:
	CCondition();
	~CCondition();

	void wait(CMutexEx &mutex);
	bool trywait(CMutexEx &mutex, long timeOut = 0);
	void signal();
	void broadcast();

private:
	ConditionInterior m_interior;
};
} //etool
#endif //ETOOL_PLATFORM_CONDITION
