/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 递归锁扩展, 支持条件变量使用
 */

#ifndef ETOOL_MUTEXEX
#define ETOOL_MUTEXEX

typedef struct _etool_mutexEx etool_mutexEx;
namespace etool {

class CMutexEx
{
	CMutexEx(const CMutexEx &mutex) { this->m_mutex = mutex.m_mutex; }
	CMutexEx& operator=(const CMutexEx &mutex) { this->m_mutex = mutex.m_mutex; return *this; }
public:
	friend class CCondition;
	CMutexEx() { m_mutex = etool_mutexEx_create(); }
	~CMutexEx() { etool_mutexEx_destroy(m_mutex); }

	inline void lock() { etool_mutexEx_lock(m_mutex); }
	inline bool trylock() { etool_mutexEx_trylock(m_mutex); }
	inline void unlock() { etool_mutexEx_unlock(m_mutex); }

private:
	etool_mutexEx *m_mutex;
};

class CMutexExGuard
{
public:
	CMutexExGuard(CMutexEx &mutex) : mc_mutex(mutex) { mc_mutex.lock(); }
	~CMutexExGuard() { mc_mutex.unlock(); }

private:
	CMutexEx &mc_mutex;
};
} //etool
#endif //ETOOL_MUTEX
