#include "ReadWriteMutex.h"


etool_readWriteMutex* etool_readWriteMutex_create()
{
	etool_readWriteMutex *mutex = malloc(sizeof(etool_readWriteMutex));
	if (mutex == 0) { return 0; }
	mutex->readCount = 0;
	if (etool_mutex_load(&(mutex->readMutex)) != 0) {
		return 0;
	}
	if (etool_recursiveMutex_load(&(mutex->writeMutex)) != 0) {
		etool_mutex_unload(&(mutex->readMutex));
		return 0;
	}
	return mutex;
}

int etool_readWriteMutex_load(etool_readWriteMutex *mutex)
{
	mutex->readCount = 0;
	if (etool_mutex_load(&(mutex->readMutex)) != 0) {
		return -1;
	}
	if (etool_recursiveMutex_load(&(mutex->writeMutex)) != 0) {
		etool_mutex_unload(&(mutex->readMutex));
		return -1;
	}
	return 0;
}

void etool_readWriteMutex_unload(etool_readWriteMutex *mutex)
{
	etool_mutex_unload(&(mutex->readMutex));
	etool_recursiveMutex_unload(&(mutex->writeMutex));
}

void etool_readWriteMutex_destroy(etool_readWriteMutex *mutex)
{
	etool_mutex_unload(&(mutex->readMutex));
	etool_recursiveMutex_unload(&(mutex->writeMutex));
	free(mutex);
}

void etool_readWriteMutex_lockRead(etool_readWriteMutex *mutex)
{
	etool_mutex_lock(&(mutex->readMutex));
	if (mutex->readCount++ == 0) {
		etool_recursiveMutex_lock(&(mutex->writeMutex));
	}
	etool_mutex_unlock(&(mutex->readMutex));
}

int etool_readWriteMutex_trylockRead(etool_readWriteMutex *mutex)
{
	if (etool_mutex_trylock(&(mutex->readMutex))) {
		if (mutex->readCount == 0) {
			if (!etool_recursiveMutex_trylock(&(mutex->writeMutex))) {
				etool_mutex_unlock(&(mutex->readMutex));
				return -1;
			}
		}

		mutex->readCount++;
		etool_mutex_unlock(&(mutex->readMutex));
		return 0;	
	}
	else {
		return -1;
	}
}

void etool_readWriteMutex_unlockRead(etool_readWriteMutex *mutex)
{
	etool_mutex_lock(&(mutex->readMutex));
	if (--mutex->readCount == 0) {
		etool_recursiveMutex_unlock(&(mutex->writeMutex));
	}
	etool_mutex_unlock(&(mutex->readMutex));
}

void etool_readWriteMutex_lockWrite(etool_readWriteMutex *mutex)
{
	etool_recursiveMutex_lock(&(mutex->writeMutex));
}

int etool_readWriteMutex_trylockWrite(etool_readWriteMutex *mutex)
{
	return etool_recursiveMutex_trylock(&(mutex->writeMutex));
}

void etool_readWriteMutex_unlockWrite(etool_readWriteMutex *mutex)
{
	etool_recursiveMutex_unlock(&(mutex->writeMutex));
}
