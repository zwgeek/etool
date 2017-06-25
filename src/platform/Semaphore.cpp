#include "semaphore.h"

namespace etool {

CSemaphore::CSemaphore(int initNum)
{
#if defined(_windows)
	//default security attributes and unnamed semaphore, _maxNum = 10
	m_interior.semaphore = CreateSemaphore(0, initNum, 10, 0);
#endif

#if defined(_linux) || defined(_android)
	sem_init(&(m_interior.semaphore), 0, initNum);
#endif

#if defined(_mac) || defined(_ios)
	semaphore_create(mach_task_self(), &(m_interior.semaphore), SYNC_POLICY_FIFO, initNum);
#endif
}

CSemaphore::~CSemaphore()
{
#if defined(_windows)
	CloseHandle(m_interior.semaphore);
#endif

#if defined(_linux) || defined(_android)
	sem_destroy(&(m_interior.semaphore));
#endif

#if defined(_mac) || defined(_ios)
	semaphore_destroy(mach_task_self(), m_interior.semaphore);
#endif
}

void CSemaphore::pend()
{
#if defined(_windows)
	WaitForSingleObject(m_interior.semaphore, INFINITE);
#endif

#if defined(_linux) || defined(_android)
	sem_wait(&(m_interior.semaphore));
#endif

#if defined(_mac) || defined(_ios)
	semaphore_wait(m_interior.semaphore);
#endif
}

bool CSemaphore::trypend(long timeOut)
{
#if defined(_windows)
	return WaitForSingleObject(m_interior.semaphore, timeOut) == 0;
#endif

#if defined(_linux) || defined(_android)
	if (timeOut != 0)
	{ 
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		ts.tv_nsec += timeOut * 1000000;
		ts.tv_sec += ts.tv_nsec / 1000000000;
		ts.tv_nsec = ts.tv_nsec % 1000000000;
		return sem_timedwait(&(m_interior.semaphore), &ts) == 0;
	} 
	else 
	{
		return sem_trywait(&(m_interior.semaphore)) == 0;
	}
#endif

#if defined(_mac) || defined(_ios)
	// if (timeOut != 0)
	// {
	// 	mach_timespec_t wait_time = {0, timeOut * 1000000};
	// 	return semaphore_timedwait(m_interior.semaphore, wait_time) == 0;
	// }
	// else
	// {
	mach_timespec_t wait_time = {0, (clock_res_t)timeOut * 1000000};
	return semaphore_timedwait(m_interior.semaphore, wait_time) == 0;
	// }
#endif
}

void CSemaphore::post()
{
#if defined(_windows)
	//can't use the lpPreviousCount
	ReleaseSemaphore(m_interior.semaphore, 1, 0);
#endif

#if defined(_linux) || defined(_android)
	sem_post(&(m_interior.semaphore));
#endif

#if defined(_mac) || defined(_ios)
	semaphore_signal(m_interior.semaphore);
#endif
}

} //etool
