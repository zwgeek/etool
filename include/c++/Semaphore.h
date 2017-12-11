/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 信号量 POSIX 无名
 */

#ifndef ETOOL_SEMAPHORE
#define ETOOL_SEMAPHORE

typedef struct _etool_semaphore etool_semaphore;
namespace etool {

class CSemaphore
{
	CSemaphore(const CSemaphore &semaphore) { this->m_semaphore = semaphore.m_semaphore; }
	CSemaphore& operator=(const CSemaphore &semaphore) { this->m_semaphore = semaphore.m_semaphore; return *this; }
public:
	CSemaphore(int initNum = 1) : m_semaphore(etool_semaphore_create(initNum)) {}
	~CSemaphore() { etool_semaphore_destroy(m_semaphore); }

	void pend() { etool_semaphore_pend(m_semaphore); }
	int trypend(const int timeOut = 0) { return etool_semaphore_trypend(m_semaphore, timeOut); }
	void post() { etool_semaphore_post(m_semaphore); }

private:
	etool_semaphore *m_semaphore;
};
} //etool
#endif //ETOOL_SEMAPHOR