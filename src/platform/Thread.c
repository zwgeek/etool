#include "Thread.h"


unsigned long etool_thread_getCurrentID()
{
#if defined(_windows)
	return GetCurrentThreadId();
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return (unsigned long)pthread_self();
#endif
}

etool_thread* etool_thread_create()
{
	etool_thread *thread = malloc(sizeof(etool_thread));
	if (thread == 0) { return 0; }
	thread->loop = 0;
	return thread;
}

void etool_thread_load(etool_thread *thread)
{
	thread->loop = 0;
}

void etool_thread_unload(etool_thread *thread)
{
	etool_thread_end(thread);
}

void etool_thread_destroy(etool_thread *thread)
{
	etool_thread_end(thread);
	free(thread);
}

int etool_thread_loop(etool_thread *thread)
{
	return thread->loop;
}

void etool_thread_start(etool_thread *thread, etool_threadPorc *porc)
{
#if defined(_windows)
	thread->thread = (HANDLE)_beginthreadex(0, 0, g_threadPorc, porc, 0, 0);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD _CREATE_JOINABLE(state)
	pthread_create(&(thread->thread), 0, g_threadPorc, porc);
#endif
}

void etool_thread_end(etool_thread *thread)
{
	thread->loop = -1;
#if defined(_windows)
	WaitForSingleObject(thread->thread, INFINITE);
	CloseHandle(thread->thread);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_join(thread->thread, 0);
#endif
}

int etool_thread_cancel(etool_thread *thread)
{
	thread->loop = -1;
#if defined(_windows)
	if (WaitForSingleObject(thread->thread, 0) == 0)
	{
		CloseHandle(thread->thread);
		return 0;
	}
	else
		return -1;

#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD_CREATE_DETACHED(state)
	pthread_detach(thread->thread);
	return 0;
#endif
}

void etool_thread_terminate(etool_thread *thread)
{
	thread->loop = -1;
#if defined(_windows)
	//the function is asyn, dwExitCode = 0
	TerminateThread(thread->thread, 0);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD_CANCEL_ENABLE(default)
	pthread_cancel(thread->thread);
#endif
}