/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 线程
 */

#ifndef ETOOL_THREAD
#define ETOOL_THREAD

typedef void etool_threadProc(void *param);
typedef struct _etool_thread etool_thread;
namespace etool {

class CThread
{
	CThread(const CThread &thread) { this->m_thread = thread.m_thread; }
	CThread& operator=(const CThread &thread) { this->m_thread = thread.m_thread; return *this; }
public:
	CThread() : m_thread(etool_thread_create()) {}
	~CThread() { etool_thread_destroy(m_thread); }

	inline static unsigned long getCurrentID() { return etool_thread_getCurrentID(); }
	inline short loop() { return etool_thread_loop(m_thread); }
	inline void start(void *param) { etool_thread_start(m_thread, this->threadProc, param); }
	inline void end() { etool_thread_end(m_thread); }
	inline int cancel() { return etool_thread_cancel(m_thread); }
	inline void terminate() { etool_thread_terminate(m_thread); }

	virtual void threadProc(void *param) = 0;
private:
	etool_thread *m_thread;
};
} //etool
#endif //ETOOL_SEMAPHOR