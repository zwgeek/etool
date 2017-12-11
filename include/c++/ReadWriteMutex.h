/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 读写锁(可递归)
 */

#ifndef ETOOL_READWRITEMUTEX
#define ETOOL_READWRITEMUTEX

typedef struct _etool_readWriteMutex etool_readWriteMutex;
namespace etool {

class CReadWriteMutex
{
	CReadWriteMutex(const CReadWriteMutex &mutex) { this->m_mutex = mutex.m_mutex; }
	CReadWriteMutex& operator=(const CReadWriteMutex&) { this->m_mutex = mutex.m_mutex; return *this; }
public:
	CReadWriteMutex() : m_mutex(etool_readWriteMutex_create()) {}
	~CReadWriteMutex() { etool_readWriteMutex_destroy(m_mutex); }

	inline void lockRead() { etool_readWriteMutex_lockRead(m_mutex); }
	inline int trylockRead() { return etool_readWriteMutex_trylockRead(m_mutex); }
	inline void unlockRead() { etool_readWriteMutex_unlockRead(m_mutex); }
	inline void lockWrite() { etool_readWriteMutex_lockWrite(m_mutex); }
	inline int trylockWrite() { return etool_readWriteMutex_trylockWrite(m_mutex); }
	inline void unlockWrite() { etool_readWriteMutex_unlockWrite(m_mutex); }

private:
	etool_readWriteMutex *m_mutex;
};

class CReadMutexGuard
{
public:
	CReadMutexGuard(CReadWriteMutex &mutex) : mc_mutex(mutex) { mc_mutex.lockRead(); }
	~CReadMutexGuard() { mc_mutex.unlockRead(); }

private:
	CReadWriteMutex &mc_mutex;
};

class CWriteMutexGuard
{
public:
	CReadMutexGuard(CReadWriteMutex &mutex) : mc_mutex(mutex) { mc_mutex.lockWrite(); }
	~CReadMutexGuard() { mc_mutex.unlockWrite(); }
	
private:
	CReadWriteMutex &mc_mutex;
};
} //etool
#endif //ETOOL_READWRITEMUTEX
