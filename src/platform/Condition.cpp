#include "Condition.h"

namespace etool {

CCondition::CCondition()
{
#if defined(_windows)
	//default security attributes and unnamed semaphore, _maxNum = 10
	m_interior.waiters = 0; 
	m_interior.cond = CreateSemaphore(0, 0, 10, 0); 
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_init(&(m_interior.cond), 0);
#endif
}

CCondition::~CCondition()
{
#if defined(_windows)
	CloseHandle(m_interior.cond); 
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_destroy(&(m_interior.cond));
#endif
}

void CCondition::wait(CMutexEx &mutex)
{
#if defined(_windows)
	m_interior.waiters++;
	SignalObjectAndWait(mutex.m_interior.mutex, m_interior.cond, INFINITE, FALSE);
	WaitForSingleObject(mutex.m_interior.mutex, INFINITE);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_wait(&(m_interior.cond), &(mutex.m_interior.mutex));
#endif
}

bool CCondition::trywait(CMutexEx &mutex, long timeOut)
{
#if defined(_windows)
	m_interior.waiters++; 
	if (SignalObjectAndWait(mutex.m_interior.mutex, m_interior.cond, timeOut, FALSE) == 0)
	{
		WaitForSingleObject(mutex.m_interior.mutex, INFINITE);
		return true; 
	}
	//函数等待超时,指定内核对象状态为未触发.
	WaitForSingleObject(mutex.m_interior.mutex, INFINITE);
	m_interior.waiters--;
	return false;
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	struct timespec ts;
#if defined(_mac)
	struct timeval now;
 	gettimeofday(&now, NULL);
 	now.tv_usec += timeOut * 1000;
 	ts.tv_sec = now.tv_sec + now.tv_usec/1000000;
 	ts.tv_nsec = now.tv_usec % 1000000 * 1000;
#else
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_nsec += timeOut * 1000000;
	ts.tv_sec += ts.tv_nsec / 1000000000;
	ts.tv_nsec = ts.tv_nsec % 1000000000;
#endif
	return pthread_cond_timedwait(&(m_interior.cond), &((mutex.m_interior.mutex)), &ts) == 0;
#endif
}

void CCondition::signal()
{
#if defined(_windows)
	//can't use the lpPreviousCount
	if (m_interior.waiters > 0)
	{
		m_interior.waiters--;
		ReleaseSemaphore(m_interior.cond, 1, 0);
	}
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_signal(&(m_interior.cond));
#endif
}

void CCondition::broadcast()
{
#if defined(_windows)
	//can't use the lpPreviousCount; 
	if (m_interior.waiters > 0)
	{
		ReleaseSemaphore(m_interior.cond, m_interior.waiters, 0);
		m_interior.waiters = 0;
	}
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_broadcast(&(m_interior.cond));
#endif
}

} //etool
