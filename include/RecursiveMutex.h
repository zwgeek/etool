/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 递归锁
 */

#ifndef ETOOL_RECURSIVEMUTEX
#define ETOOL_RECURSIVEMUTEX

namespace etool {

struct RecursiveMutexInterior;
class CRecursiveMutex
{
	CRecursiveMutex(const CRecursiveMutex&);
	CRecursiveMutex& operator=(const CRecursiveMutex&);
public:
	CRecursiveMutex();
	~CRecursiveMutex();

	inline void lock();
	inline bool trylock();
	inline void unlock();

private:
	RecursiveMutexInterior m_interior;
};


class CRecursiveMutexGuard
{
public:
	CRecursiveMutexGuard(CRecursiveMutex &mutex) : m_mutex(mutex) {m_mutex.lock(); }
	~CRecursiveMutexGuard() {m_mutex.unlock(); }

private:
	CRecursiveMutex &m_mutex;
};
} //etool
#endif //ETOOL_RECURSIVEMUTEX
