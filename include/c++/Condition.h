/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 条件变量
 */

#ifndef ETOOL_CONDITION
#define ETOOL_CONDITION

typedef struct _etool_condition etool_condition;
namespace etool {

class CCondition
{
	CCondition(const CCondition &condition) { this->m_condition = condition.m_condition; }
	CCondition& operator=(const CCondition &condition) { this->m_condition = condition.m_condition; return *this; }
public:
	CCondition() { m_condition = etool_condition_create(); }
	~CCondition() { etool_condition_destroy(m_condition); }

	inline void wait(CMutex *mutex) { etool_condition_wait(m_condition, mutex->m_mutex); }
	inline bool trywait(CMutex *mutex, const int timeOut = 10) { return etool_condition_trywait(m_condition, mutex->m_mutex, timeOut); }
	inline void signal() { etool_condition_signal(m_condition); }
	inline void broadcast() { etool_condition_broadcast(m_condition); }

private:
	etool_condition *m_condition;
};
} //etool
#endif //ETOOL_CONDITION
