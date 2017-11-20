/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 信号量 POSIX 无名
 */

#ifndef ETOOL_SEMAPHORE
#define ETOOL_SEMAPHORE

namespace etool {

struct SemaphoreInterior;
class CSemaphore
{
	CSemaphore(const CSemaphore&);
	CSemaphore& operator=(const CSemaphore&);
public:
	CSemaphore(int initNum = 1);
	~CSemaphore();

	void pend();
	void trypend(long timeOut = 0);
	void post();

private:
	SemaphoreInterior m_interior;
};

} //etool
#endif //ETOOL_SEMAPHOR