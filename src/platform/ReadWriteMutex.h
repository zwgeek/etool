/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 读写锁(可递归)
 */

#ifndef ETOOL_PLATFORM_READWRITEMUTEX
#define ETOOL_PLATFORM_READWRITEMUTEX

#include "Mutex.h"
#include "RecursiveMutex.h"

namespace etool {

class CReadWriteMutex
{
	CReadWriteMutex(const CReadWriteMutex&) {}
	CReadWriteMutex& operator=(const CReadWriteMutex&) { return *this; }
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
	int                         m_readCount;
	CMutex                 m_readMutex;
	CRecursiveMutex m_writeMutex;
};
} //etool
#endif //ETOOL_PLATFORM_READWRITEMUTEX
