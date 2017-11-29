#include "Condition.h"


etool_condition* etool_condition_create()
{
	etool_condition *condition = malloc(sizeof(etool_condition));
	if (condition == 0) { return 0; }
#if defined(_windows)
	//default security attributes and unnamed semaphore, _maxNum = 10
	condition->waiters = 0;
	condition->cond = CreateSemaphore(0, 0, 10, 0);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_init(&(condition->cond), 0);
#endif
	return condition;
}

int etool_condition_load(etool_condition *condition)
{
#if defined(_windows)
	//default security attributes and unnamed semaphore, _maxNum = 10
	condition->waiters = 0;
	condition->cond = CreateSemaphore(0, 0, 10, 0);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_init(&(condition->cond), 0);
#endif
	return 0;
}

void etool_condition_unload(etool_condition *condition)
{
#if defined(_windows)
	CloseHandle(condition->cond);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_destroy(&(condition->cond));
#endif
}

void etool_condition_destroy(etool_condition *condition)
{
#if defined(_windows)
	CloseHandle(condition->cond);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_destroy(&(condition->cond));
#endif
	free(condition);
}

void etool_condition_wait(etool_condition *condition, etool_mutexEx *mutex)
{
#if defined(_windows)
	condition->waiters++;
	SignalObjectAndWait(mutex->mutex, condition->cond, INFINITE, FALSE);
	WaitForSingleObject(mutex->mutex, INFINITE);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_wait(&(condition->cond), &(mutex->mutex));
#endif
}

int etool_condition_trywait(etool_condition*condition, etool_mutexEx *mutex, const int timeOut)
{
#if defined(_windows)
	condition->waiters++;
	if (SignalObjectAndWait(mutex->mutex, condition->cond, timeOut, FALSE) == 0)
	{
		WaitForSingleObject(mutex->mutex, INFINITE);
		return 0;
	}
	//函数等待超时,指定内核对象状态为未触发.
	WaitForSingleObject(mutex->mutex, INFINITE);
	condition->waiters--;
	return -1;
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
	return pthread_cond_timedwait(&(condition->cond), &((mutex->mutex)), &ts);
#endif
}

void etool_condition_signal(etool_condition*condition)
{
#if defined(_windows)
	//can't use the lpPreviousCount
	if (condition->waiters > 0)
	{
		ReleaseSemaphore(condition->cond, 1, 0);
		condition->waiters--;
	}
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_signal(&(condition->cond));
#endif
}

void etool_condition_broadcast(etool_condition*condition)
{
#if defined(_windows)
	//can't use the lpPreviousCount;
	if (condition->waiters > 0)
	{
		ReleaseSemaphore(condition->cond, condition->waiters, 0);
		condition->waiters = 0;
	}
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_cond_broadcast(&(condition->cond));
#endif
}
