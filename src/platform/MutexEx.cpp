#include "MutexEx.h"

namespace etool {

CMutexEx::CMutexEx()
{
#if defined(_windows)
	m_interior.mutex = CreateMutex(0, FALSE, 0);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_init(&(m_interior.mutex), 0);
#endif
}

CMutexEx::~CMutexEx()
{
#if defined(_windows)
	CloseHandle(m_interior.mutex);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_destroy(&(m_interior.mutex));
#endif
}

void CMutexEx::lock()
{
#if defined(_windows)
	WaitForSingleObject(m_interior.mutex, INFINITE);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_lock(&(m_interior.mutex));
#endif
}

bool CMutexEx::trylock()
{
#if defined(_windows)
	return WaitForSingleObject(m_interior.mutex, 0) == 0;
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	return pthread_mutex_trylock(&(m_interior.mutex)) == 0;
#endif
}

void CMutexEx::unlock()
{
#if defined(_windows)
	ReleaseMutex(m_interior.mutex);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	pthread_mutex_unlock(&(m_interior.mutex));
#endif
}

} //etool
