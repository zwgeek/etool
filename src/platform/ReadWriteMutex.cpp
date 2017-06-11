#include "ReadWriteMutex.h"

namespace etool {

CReadWriteMutex::CReadWriteMutex()
: m_readCount(0) {}

CReadWriteMutex::~CReadWriteMutex() {}

void CReadWriteMutex::lockRead()
{
	m_readMutex.lock();
	if (m_readCount++ == 0) {
		m_writeMutex.lock();
	}
	m_readMutex.unlock();
}

bool CReadWriteMutex::trylockRead()
{
	if (m_readMutex.trylock()) {
		if (m_writeMutex.trylock()) {
			m_readCount++;
			m_readMutex.unlock();
			return true;
		}
		else {
			m_readMutex.unlock();
			return false;
		}
	}
	else {
		return false;
	}
}

void CReadWriteMutex::unlockRead()
{
	m_readMutex.lock();
	if (--m_readCount == 0) {
		m_writeMutex.unlock();
	}
	m_readMutex.unlock();
}

void CReadWriteMutex::lockWrite()
{
	m_writeMutex.lock();
}

bool CReadWriteMutex::trylockWrite()
{
	return m_writeMutex.trylock();
}

void CReadWriteMutex::unlockWrite()
{
	m_writeMutex.unlock();
}
} //etool
