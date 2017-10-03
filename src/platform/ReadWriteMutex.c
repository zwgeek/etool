#include "ReadWriteMutex.h"


int etool_readWriteMutex_create(etool_readWriteMutex *mutex)
{
	*mutex = malloc(sizeof(struct etool_readWriteMutexInterior));
	if ((*mutex) == 0) { return -1; }
	(*mutex)->readCount = 0;
	etool_mutex_create(&((*mutex)->readMutex));
	etool_recursiveMutex_create(&((*mutex)->writeMutex));
	return 0;
}

void etool_readWriteMutex_destroy(etool_readWriteMutex *mutex)
{
	etool_mutex_destroy(&((*mutex)->readMutex));
	etool_recursiveMutex_destroy(&((*mutex)->writeMutex));
	free(*mutex);
}

void etool_readWriteMutex_lockRead(etool_readWriteMutex *mutex)
{
	etool_mutex_lock(&((*mutex)->readMutex));
	if ((*mutex)->readCount++ == 0) {
		etool_recursiveMutex_lock(&((*mutex)->writeMutex));
	}
	etool_mutex_unlock(&((*mutex)->readMutex));
}

int etool_readWriteMutex_trylockRead(etool_readWriteMutex *mutex)
{
	if (etool_mutex_trylock(&((*mutex)->readMutex))) {
		if ((*mutex)->readCount == 0) {
			if (!etool_recursiveMutex_trylock(&((*mutex)->writeMutex))) {
				etool_mutex_unlock(&((*mutex)->readMutex));
				return -1;
			}
		}

		(*mutex)->readCount++;
		etool_mutex_unlock(&((*mutex)->readMutex));
		return 0;	
	}
	else {
		return -1;
	}
}

void etool_readWriteMutex_unlockRead(etool_readWriteMutex *mutex)
{
	etool_mutex_lock(&((*mutex)->readMutex));
	if (--(*mutex)->readCount == 0) {
		etool_recursiveMutex_unlock(&((*mutex)->writeMutex));
	}
	etool_mutex_unlock(&((*mutex)->readMutex));
}

void etool_readWriteMutex_lockWrite(etool_readWriteMutex *mutex)
{
	etool_recursiveMutex_lock(&((*mutex)->writeMutex));
}

int etool_readWriteMutex_trylockWrite(etool_readWriteMutex *mutex)
{
	return etool_recursiveMutex_trylock(&((*mutex)->writeMutex));
}

void etool_readWriteMutex_unlockWrite(etool_readWriteMutex *mutex)
{
	etool_recursiveMutex_unlock(&((*mutex)->writeMutex));
}
