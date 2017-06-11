/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 线程
 */

#ifndef ETOOL_PLATFORM_THREAD
#define ETOOL_PLATFORM_THREAD

#if defined(_windows)
#include <windows.h>
#include <process.h> 
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
#include <pthread.h>
#endif

namespace etool {

struct ThreadInterior {
	bool         loop;
#if defined(_windows)
	HANDLE thread;
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_t thread;
#endif
};

class CThread
{
	CThread(const CThread&) {}
	CThread& operator=(const CThread&) { return *this; }

public:
	CThread();
	~CThread();

	virtual void threadPorc() = 0;
	static unsigned long getCurrentID();

protected:
	bool loop();
	void createThread();
	void destroyThread();
	bool cancelThread();
	void terminateThread();

private:
	ThreadInterior m_interior;
};

#if defined(_windows)
	unsigned int __stdcall g_threadPorc(void *self) {((CThread*)self)->threadPorc(); return 0;}
#endif
#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	void* g_threadPorc(void *self) {((CThread*)self)->threadPorc(); return 0;}
#endif

} //etool
#endif //ETOOL_PLATFORM_THREAD
