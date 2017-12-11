/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 互斥锁
 */

#ifndef ETOOL_MUTEX
#define ETOOL_MUTEX

typedef struct _etool_mutex etool_mutex;
namespace etool {

class CMutex
{
	CMutex(const CMutex &mutex) { this->m_mutex = mutex.m_mutex; }
	CMutex& operator=(const CMutex &mutex) { this->m_mutex = mutex.m_mutex; return *this; }
public:
	CMutex() { m_mutex = etool_mutex_create(); }
	~CMutex() { etool_mutex_destroy(m_mutex); }

	inline void lock() { etool_mutex_lock(m_mutex); }
	inline bool trylock() { etool_mutex_trylock(m_mutex); }
	inline void unlock() { etool_mutex_unlock(m_mutex); }

private:
	etool_mutex *m_mutex;
};

class CMutexGuard
{
public:
	CMutexGuard(CMutex &mutex) : mc_mutex(mutex) { mc_mutex.lock(); }
	~CMutexGuard() { mc_mutex.unlock(); }

private:
	CMutex &mc_mutex;
};
} //etool
#endif //ETOOL_MUTEX
