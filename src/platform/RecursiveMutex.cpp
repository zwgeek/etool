#include "RecursiveMutex.h"

namespace etool {

CRecursiveMutex::CRecursiveMutex()
{
#if defined(_windows)
	//旋转锁，单cpu不起作用
	InitializeCriticalSectionAndSpinCount(&(m_interior.mutex), 0x00000400);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutexattr_t attr; 
	pthread_mutexattr_init(&attr); 
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&(m_interior.mutex), &attr); 
	pthread_mutexattr_destroy(&attr);
#endif
}

CRecursiveMutex::~CRecursiveMutex()
{
#if defined(_windows)
	DeleteCriticalSection(&(m_interior.mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_destroy(&(m_interior.mutex));
#endif
}

void CRecursiveMutex::lock()
{
#if defined(_windows)
	EnterCriticalSection(&(m_interior.mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_lock(&(m_interior.mutex));
#endif
}

bool CRecursiveMutex::trylock()
{
#if defined(_windows)
	return TryEnterCriticalSection(&(m_interior.mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	return pthread_mutex_trylock(&(m_interior.mutex)) == 0;
#endif
}

void CRecursiveMutex::unlock()
{
#if defined(_windows)
	LeaveCriticalSection(&(m_interior.mutex));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_unlock(&(m_interior.mutex));
#endif
}

} //etool
