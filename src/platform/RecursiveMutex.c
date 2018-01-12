#include "RecursiveMutex.h"


etool_recursiveMutex* etool_recursiveMutex_create()
{
	etool_recursiveMutex *mutex = (etool_recursiveMutex*)malloc(sizeof(etool_recursiveMutex));
	if (mutex == 0) { return 0; }
#if defined(_windows)
	//旋转锁，单cpu不起作用
	InitializeCriticalSectionAndSpinCount(&(mutex->mutex), 0x00000400);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutexattr_t attr; 
	pthread_mutexattr_init(&attr); 
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&(mutex->mutex), &attr); 
	pthread_mutexattr_destroy(&attr);
#endif
	return mutex;
}

int etool_recursiveMutex_load(etool_recursiveMutex *mutex)
{
#if defined(_windows)
	//旋转锁，单cpu不起作用
	InitializeCriticalSectionAndSpinCount(&(mutex->mutex), 0x00000400);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutexattr_t attr; 
	pthread_mutexattr_init(&attr); 
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&(mutex->mutex), &attr); 
	pthread_mutexattr_destroy(&attr);
#endif
	return 0;
}

void etool_recursiveMutex_unload(etool_recursiveMutex *mutex)
{
#if defined(_windows)
	DeleteCriticalSection(&(mutex->mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_destroy(&(mutex->mutex));
#endif
}

void etool_recursiveMutex_destroy(etool_recursiveMutex *mutex)
{
#if defined(_windows)
	DeleteCriticalSection(&(mutex->mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_destroy(&(mutex->mutex));
#endif
	free(mutex);
}

void etool_recursiveMutex_lock(etool_recursiveMutex *mutex)
{
#if defined(_windows)
	EnterCriticalSection(&(mutex->mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_lock(&(mutex->mutex));
#endif
}

int etool_recursiveMutex_trylock(etool_recursiveMutex *mutex)
{
#if defined(_windows)
	return TryEnterCriticalSection(&(mutex->mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	return pthread_mutex_trylock(&(mutex->mutex));
#endif
}

void etool_recursiveMutex_unlock(etool_recursiveMutex *mutex)
{
#if defined(_windows)
	LeaveCriticalSection(&(mutex->mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_unlock(&(mutex->mutex));
#endif
}
