#include "Thread.h"

namespace etool {

CThread::CThread() { m_interior.loop = true; }

CThread::~CThread() {}

unsigned long getCurrentID()
{
#if defined(_windows)
	return ::GetCurrentThreadId();
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return pthread_self();
#endif
}

bool CThread::loop()
{
	return m_interior.loop;
}

void CThread::createThread()
{
#if defined(_windows)
	m_interior.thread = (HANDLE)_beginthreadex(NULL, 0, g_threadPorc, this, 0, NULL);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD _CREATE_JOINABLE(state)
	pthread_create(&m_interior.thread, NULL, threadPorc, this);
#endif
}

void CThread::destroyThread()
{
	m_interior.loop = false;
#if defined(_windows)
	WaitForSingleObject(m_interior.thread, INFINITE);
	CloseHandle(m_interior.thread);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_join(&m_interior.thread, NULL);
#endif
}

bool CThread::cancelThread()
{
	m_interior.loop = false;
#if defined(_windows)
	if (WaitForSingleObject(m_interior.thread, 0) == 0)
	{
		CloseHandle(m_interior.thread);
		return true;
	}
	else
		return false;

#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD_CREATE_DETACHED(state)
	pthread_detach(&m_interior.thread);
	return true;
#endif
}

void CThread::terminateThread()
{
	m_interior.loop = false;
#if defined(_windows)
	//the function is asyn, dwExitCode = 0
	TerminateThread(m_interior.thread, 0);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD_CANCEL_ENABLE(default)
	pthread_cancel(&m_interior.thread);
#endif
}

} //etool
