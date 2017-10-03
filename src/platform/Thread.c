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

int etool_thread_create(etool_thread *thread)
{ 
	*thread = malloc(sizeof(struct etool_threadInterior));
	if ((*thread) == 0) { return -1; }
	(*thread)->loop = 0;
	return 0;
}

void etool_thread_destroy(etool_thread *thread)
{
	free(*thread);
}

int etool_thread_loop(etool_thread *thread)
{
	return (*thread)->loop;
}

void etool_thread_start(etool_thread *thread, etool_threadPorc *porc)
{
#if defined(_windows)
	(*thread)->thread = (HANDLE)_beginthreadex(NULL, 0, g_threadPorc, porc, 0, NULL);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD _CREATE_JOINABLE(state)
	pthread_create(&(*thread)->thread, NULL, g_threadPorc, porc);
#endif
}

void etool_thread_end(etool_thread *thread)
{
	(*thread)->loop = -1;
#if defined(_windows)
	WaitForSingleObject((*thread)->thread, INFINITE);
	CloseHandle((*thread)->thread);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	pthread_join((*thread)->thread, NULL);
#endif
}

int etool_thread_cancel(etool_thread *thread)
{
	(*thread)->loop = -1;
#if defined(_windows)
	if (WaitForSingleObject((*thread)->thread, 0) == 0)
	{
		CloseHandle((*thread)->thread);
		return 0;
	}
	else
		return -1;

#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD_CREATE_DETACHED(state)
	pthread_detach((*thread)->thread);
	return 0;
#endif
}

void etool_thread_terminate(etool_thread *thread)
{
	(*thread)->loop = -1;
#if defined(_windows)
	//the function is asyn, dwExitCode = 0
	TerminateThread((*thread)->thread, 0);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	//PTHREAD_CANCEL_ENABLE(default)
	pthread_cancel((*thread)->thread);
#endif
}
