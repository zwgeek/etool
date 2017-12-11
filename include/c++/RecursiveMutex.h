/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 递归锁
 */

#ifndef ETOOL_RECURSIVEMUTEX
#define ETOOL_RECURSIVEMUTEX

typedef struct _etool_recursiveMutex etool_recursiveMutex;
namespace etool {

class CRecursiveMutex
{
	CRecursiveMutex(const CRecursiveMutex &mutex) { this->m_mutex = mutex.m_mutex; }
	CRecursiveMutex& operator=(const CRecursiveMutex &mutex) { this->m_mutex = mutex.m_mutex; return *this; }
public:
	CRecursiveMutex() m_mutex(etool_recursiveMutex_create()) {}
	~CRecursiveMutex() { etool_recursiveMutex_destroy(m_mutex); }

	inline void lock() { etool_recursiveMutex_lock(m_mutex); }
	inline int trylock() { return etool_recursiveMutex_trylock(m_mutex); }
	inline void unlock() { etool_recursiveMutex_unlock(m_mutex); }

private:
	etool_recursiveMutex *m_mutex;
};


class CRecursiveMutexGuard
{
public:
	CRecursiveMutexGuard(CRecursiveMutex &mutex) : mc_mutex(mutex) {mc_mutex.lock(); }
	~CRecursiveMutexGuard() {mc_mutex.unlock(); }

private:
	CRecursiveMutex &mc_mutex;
};
} //etool
#endif //ETOOL_RECURSIVEMUTEX
