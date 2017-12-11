/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 原子计数器
 */

#ifndef ETOOL_ATOMIC
#define ETOOL_ATOMIC

typedef struct _etool_atomic etool_atomic;
namespace etool {

class CAtomic {
	CAtomic(const CAtomic &atomic) { this->m_atomic = atomic.m_atomic; }
	CAtomic& operator=(const CAtomic &atomic) {}
public:
	CAtomic(int count = 0) { m_atomic = etool_atomic_create(count); }
	~CAtomic() { etool_atomic_destroy(m_atomic); }

	inline int inc() { return etool_atomic_inc(m_atomic); }
	inline int dec() { return etool_atomic_dec(m_atomic); }
	inline int add(int count = 1) { return etool_atomic_add(m_atomic, count); }
	inline int sub(int count = 1) { return etool_atomic_sub(m_atomic, count); }
	inline int  or(int count) { return etool_atomic_or(m_atomic, count); }
	inline int and(int count) { return etool_atomic_and(m_atomic, count); }
	inline int xor(int count) { return etool_atomic_xor(m_atomic, count); }

private:
	etool_atomic *m_atomic;
};

} //etool
#endif //ETOOL_ATOMIC