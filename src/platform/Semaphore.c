#include "Semaphore.h"


//initNum = 1
etool_semaphore* etool_semaphore_create(const int initNum)
{
	etool_semaphore *semaphore = (etool_semaphore*)malloc(sizeof(etool_semaphore));
	if (semaphore == 0) { return 0; }
#if defined(_windows)
	//default security attributes and unnamed semaphore, _maxNum = initNum
	semaphore->semaphore = CreateSemaphore(0, 0, initNum, 0);
#endif

#if defined(_linux) || defined(_android)
	sem_init(&(semaphore->semaphore), 0, initNum);
#endif

#if defined(_mac) || defined(_ios)
	semaphore_create(mach_task_self(), &(semaphore->semaphore), SYNC_POLICY_FIFO, initNum);
#endif
	return semaphore;
}

int etool_semaphore_load(etool_semaphore *semaphore, const int initNum)
{
#if defined(_windows)
	//default security attributes and unnamed semaphore, _maxNum = initNum
	semaphore->semaphore = CreateSemaphore(0, 0, initNum, 0);
#endif

#if defined(_linux) || defined(_android)
	sem_init(&(semaphore->semaphore), 0, initNum);
#endif

#if defined(_mac) || defined(_ios)
	semaphore_create(mach_task_self(), &(semaphore->semaphore), SYNC_POLICY_FIFO, initNum);
#endif
	return 0;
}

void etool_semaphore_unload(etool_semaphore *semaphore)
{
#if defined(_windows)
	CloseHandle(semaphore->semaphore);
#endif

#if defined(_linux) || defined(_android)
	sem_destroy(&(semaphore->semaphore));
#endif

#if defined(_mac) || defined(_ios)
	semaphore_destroy(mach_task_self(), semaphore->semaphore);
#endif
}

void etool_semaphore_destroy(etool_semaphore *semaphore)
{
#if defined(_windows)
	CloseHandle(semaphore->semaphore);
#endif

#if defined(_linux) || defined(_android)
	sem_destroy(&(semaphore->semaphore));
#endif

#if defined(_mac) || defined(_ios)
	semaphore_destroy(mach_task_self(), semaphore->semaphore);
#endif
	free(semaphore);
}

void etool_semaphore_pend(etool_semaphore *semaphore)
{
#if defined(_windows)
	WaitForSingleObject(semaphore->semaphore, INFINITE);
#endif

#if defined(_linux) || defined(_android)
	sem_wait(&(semaphore->semaphore));
#endif

#if defined(_mac) || defined(_ios)
	semaphore_wait(semaphore->semaphore);
#endif
}

int etool_semaphore_trypend(etool_semaphore *semaphore, const int timeOut)
{
#if defined(_windows)
	return WaitForSingleObject(semaphore->semaphore, timeOut);
#endif

#if defined(_linux) || defined(_android)
	//timeOut != 0
	if (timeOut)
	{ 
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		ts.tv_nsec += timeOut * 1000000;
		ts.tv_sec += ts.tv_nsec / 1000000000;
		ts.tv_nsec = ts.tv_nsec % 1000000000;
		return sem_timedwait(&(semaphore->semaphore), &ts);
	} else {
		return sem_trywait(&(semaphore->semaphore));
	}
#endif

#if defined(_mac) || defined(_ios)
	//timeOut != 0
	// if (timeOut)
	// {
	// 	mach_timespec_t wait_time = {0, timeOut * 1000000};
	// 	return semaphore_timedwait(semaphore->semaphore, wait_time);
	// } else {
	mach_timespec_t wait_time = {0, (clock_res_t)timeOut * 1000000};
	return semaphore_timedwait(semaphore->semaphore, wait_time);
	// }
#endif
}

void etool_semaphore_post(etool_semaphore *semaphore)
{
#if defined(_windows)
	//can't use the lpPreviousCount
	ReleaseSemaphore(semaphore->semaphore, 1, 0);
#endif

#if defined(_linux) || defined(_android)
	sem_post(&(semaphore->semaphore));
#endif

#if defined(_mac) || defined(_ios)
	semaphore_signal(semaphore->semaphore);
#endif
}
