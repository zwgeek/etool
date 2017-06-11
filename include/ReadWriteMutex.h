/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 读写锁(可递归)
 */

#ifndef ETOOL_READWRITEMUTEX
#define ETOOL_READWRITEMUTEX

namespace etool {

class CMutex;
class CRecursiveMutex;
class CReadWriteMutex
{
	CReadWriteMutex(const CReadWriteMutex&);
	CReadWriteMutex& operator=(const CReadWriteMutex&);
public:
	CReadWriteMutex();
	~CReadWriteMutex();

	void lockRead();
	bool trylockRead();
	void unlockRead();
	void lockWrite();
	bool trylockWrite();
	void unlockWrite();

private:
	int                           m_readCount;
	CMutex                  m_readMutex;
	CRecursiveMutex m_writeMutex;
};

class CReadMutexGuard
{
public:
	CReadMutexGuard(CRecursiveMutex &mutex) : m_mutex(mutex) { m_mutex.lockRead(); }
	~CReadMutexGuard() { m_mutex.unlockRead(); }

private:
	CRecursiveMutex &m_mutex;
};

class CWriteMutexGuard
{
public:
	CReadMutexGuard(CRecursiveMutex &mutex) : m_mutex(mutex) { m_mutex.lockWrite(); }
	~CReadMutexGuard() { m_mutex.unlockWrite(); }
	
private:
	CRecursiveMutex &m_mutex;
};
} //etool
#endif //ETOOL_READWRITEMUTEX
