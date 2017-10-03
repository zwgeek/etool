#include "Mutex.h"


int etool_mutex_create(etool_mutex *mutex)
{
	*mutex = malloc(sizeof(struct etool_mutexInterior));
	if ((*mutex) == 0) { return -1; }
#if defined(_windows)
	//旋转锁，单cpu不起作用
	InitializeCriticalSectionAndSpinCount(&((*mutex)->mutex), 0x00000400);
#endif
	
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_init(&((*mutex)->mutex), 0);
#endif
	return 0;
}

void etool_mutex_destroy(etool_mutex *mutex)
{
#if defined(_windows)
	DeleteCriticalSection(&((*mutex)->mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_destroy(&((*mutex)->mutex));
#endif
	free(*mutex);
}

void etool_mutex_lock(etool_mutex *mutex)
{
#if defined(_windows)
	EnterCriticalSection(&((*mutex)->mutex)); 
	(*mutex)->mutex.OwningThread = 0;
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_lock(&((*mutex)->mutex));
#endif
}

int etool_mutex_trylock(etool_mutex *mutex)
{
#if defined(_windows)
	return TryEnterCriticalSection(&((*mutex)->mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	return pthread_mutex_trylock(&((*mutex)->mutex ));
#endif
}

void etool_mutex_unlock(etool_mutex *mutex)
{
#if defined(_windows)
	LeaveCriticalSection(&((*mutex)->mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_unlock(&((*mutex)->mutex));
#endif
}
