/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 互斥锁
 */

#ifndef ETOOL_MUTEX
#define ETOOL_MUTEX

namespace etool {

struct MutexInterior;
class CMutex
{
	CMutex(const CMutex&);
	CMutex& operator=(const CMutex&);
public:
	CMutex();
	~CMutex();

	void lock();
	bool trylock();
	void unlock();

private:
	MutexInterior m_interior;
};

class CMutexGuard
{
public:
	CMutexGuard(CMutex &mutex) : m_mutex(mutex) { m_mutex.lock(); }
	~CMutexGuard() { m_mutex.unlock(); }

private:
	CMutex &m_mutex;
};
} //etool
#endif //ETOOL_MUTEX
