#include "ReadWriteMutex.h"


etool_readWriteMutex* etool_readWriteMutex_create()
{
	etool_readWriteMutex *mutex = (etool_readWriteMutex*)malloc(sizeof(etool_readWriteMutex));
	if (mutex == 0) { return 0; }
#if defined(_windows)
	mutex->readCount = 0;
	if (etool_mutex_load(&(mutex->readMutex)) != 0) {
		return 0;
	}
	if (etool_recursiveMutex_load(&(mutex->writeMutex)) != 0) {
		etool_mutex_unload(&(mutex->readMutex));
		return 0;
	}
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_rwlock_init(&(mutex->mutex), 0);
#endif
	return mutex;
}

int etool_readWriteMutex_load(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	mutex->readCount = 0;
	if (etool_mutex_load(&(mutex->readMutex)) != 0) {
		return -1;
	}
	if (etool_recursiveMutex_load(&(mutex->writeMutex)) != 0) {
		etool_mutex_unload(&(mutex->readMutex));
		return -1;
	}
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_rwlock_init(&(mutex->mutex), 0);
#endif	
	return 0;
}

void etool_readWriteMutex_unload(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	etool_mutex_unload(&(mutex->readMutex));
	etool_recursiveMutex_unload(&(mutex->writeMutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_rwlock_destroy(&(mutex->mutex));
#endif
}

void etool_readWriteMutex_destroy(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	etool_mutex_unload(&(mutex->readMutex));
	etool_recursiveMutex_unload(&(mutex->writeMutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_rwlock_destroy(&(mutex->mutex));
#endif	
	free(mutex);
}

void etool_readWriteMutex_lockRead(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	etool_mutex_lock(&(mutex->readMutex));
	if (mutex->readCount++ == 0) {
		etool_recursiveMutex_lock(&(mutex->writeMutex));
	}
	etool_mutex_unlock(&(mutex->readMutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_rwlock_rdlock(&(mutex->mutex));
#endif
}

int etool_readWriteMutex_trylockRead(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	if (etool_mutex_trylock(&(mutex->readMutex)) == 0) {
		if (mutex->readCount == 0) {
			if (!etool_recursiveMutex_trylock(&(mutex->writeMutex))) {
				etool_mutex_unlock(&(mutex->readMutex));
				return -1;
			}
		}

		mutex->readCount++;
		etool_mutex_unlock(&(mutex->readMutex));
		return 0;	
	} else {
		return -1;
	}
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	return pthread_rwlock_tryrdlock(&(mutex->mutex));
#endif
}

void etool_readWriteMutex_unlockRead(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	etool_mutex_lock(&(mutex->readMutex));
	if (--mutex->readCount == 0) {
		etool_recursiveMutex_unlock(&(mutex->writeMutex));
	}
	etool_mutex_unlock(&(mutex->readMutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_rwlock_unlock(&(mutex->mutex));
#endif
}

void etool_readWriteMutex_lockWrite(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	etool_recursiveMutex_lock(&(mutex->writeMutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_rwlock_wrlock(&(mutex->mutex));
#endif
}

int etool_readWriteMutex_trylockWrite(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	return etool_recursiveMutex_trylock(&(mutex->writeMutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	return pthread_rwlock_trywrlock(&(mutex->mutex));
#endif	
}

void etool_readWriteMutex_unlockWrite(etool_readWriteMutex *mutex)
{
#if defined(_windows)
	etool_recursiveMutex_unlock(&(mutex->writeMutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_rwlock_unlock(&(mutex->mutex));
#endif
}
