#include "MutexEx.h"


etool_mutexEx* etool_mutexEx_create()
{
	etool_mutexEx *mutex = (etool_mutexEx*)malloc(sizeof(etool_mutexEx));
	if (mutex == 0) { return 0; }
#if defined(_windows)
	mutex->mutex = CreateMutex(0, FALSE, 0);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_init(&(mutex->mutex), 0);
#endif
	return mutex;
}

int etool_mutexEx_load(etool_mutexEx *mutex)
{
#if defined(_windows)
	mutex->mutex = CreateMutex(0, FALSE, 0);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_init(&(mutex->mutex), 0);
#endif
	return 0;
}

void etool_mutexEx_unload(etool_mutexEx *mutex)
{
#if defined(_windows)
	CloseHandle(mutex->mutex);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_destroy(&(mutex->mutex));
#endif
}

void etool_mutexEx_destroy(etool_mutexEx *mutex)
{
#if defined(_windows)
	CloseHandle(mutex->mutex);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_destroy(&(mutex->mutex));
#endif
	free(mutex);
}

void etool_mutexEx_lock(etool_mutexEx *mutex)
{
#if defined(_windows)
	WaitForSingleObject(mutex->mutex, INFINITE);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_lock(&(mutex->mutex));
#endif
}

int etool_mutexEx_trylock(etool_mutexEx *mutex)
{
#if defined(_windows)
	return WaitForSingleObject(mutex->mutex, 0);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	return pthread_mutex_trylock(&(mutex->mutex));
#endif
}

void etool_mutexEx_unlock(etool_mutexEx *mutex)
{
#if defined(_windows)
	ReleaseMutex(mutex->mutex);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_unlock(&(mutex->mutex));
#endif
}
