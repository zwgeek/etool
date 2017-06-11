/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * Task 自动推导类
 */

#ifndef ETOOL_TASK
#define ETOOL_TASK

class ITask {
public:
	ITask(int straget) : m_straget(straget) {}
	~ITask() {}

	inline int getStraget() { return m_straget; }
	virtual void operator ()(void *thread) = 0;
	//inline bool operator ==(ITask &task) { return m_straget == task.getStraget(); }
	
private:
	int m_straget;
};

template <class T1 = int, class T2 = int, class T3 = int, class T4 = int, class T5 = int, class T6 = int>
class CTask : public ITask
{
public:
	typedef void (*F0)(void*);
	typedef void (*F1)(T1, void*);
	typedef void (*F2)(T1, T2, void*);
	typedef void (*F3)(T1, T2, T3, void*);
	typedef void (*F4)(T1, T2, T3, T4, void*);
	typedef void (*F5)(T1, T2, T3, T4, T5, void*);
	typedef void (*F6)(T1, T2, T3, T4, T5, T6, void*);

	CTask(F0 f, int straget) : f0(f), f1(0), f2(0), f3(0), f4(0), f5(0), f6(0), ITask(straget) {}
	CTask(F1 f, T1 _t1, int straget) : f0(0), f1(f), f2(0), f3(0), f4(0), f5(0), f6(0), t1(_t1), ITask(straget) {}
	CTask(F2 f, T1 _t1, T2 _t2, int straget) : f0(0), f1(0), f2(f), f3(0), f4(0), f5(0), f6(0), t1(_t1), t2(_t2), ITask(straget) {}
	CTask(F3 f, T1 _t1, T2 _t2, T3 _t3, int straget) : f0(0), f1(0), f2(0), f3(f), f4(0), f5(0), f6(0), t1(_t1), t2(_t2), t3(_t3), ITask(straget) {}
	CTask(F4 f, T1 _t1, T2 _t2, T3 _t3, T4 _t4, int straget) : f0(0), f1(0), f2(0), f3(0), f4(f), f5(0), f6(0), t1(_t1), t2(_t2), t3(_t3), t4(_t4), ITask(straget) {}
	CTask(F5 f, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, int straget) : f0(0), f1(0), f2(0), f3(0), f4(0), f5(f), f6(0), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5), ITask(straget) {}
	CTask(F6 f, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, int straget) : f0(0), f1(0), f2(0), f3(0), f4(0), f5(0), f6(f), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5), t6(_t6), ITask(straget) {}

	void operator ()(void *thread)
	{
		if (f0) {return f0(thread);}
		if (f1) {return f1(t1, thread);}
		if (f2) {return f2(t1, t2, thread);}
		if (f3) {return f3(t1, t2, t3, thread);}
		if (f4) {return f4(t1, t2, t3, t4, thread);}
		if (f5) {return f5(t1, t2, t3, t4, t5, thread);}
		if (f6) {return f6(t1, t2, t3, t5, t6, thread);}
	}

private:
	F0 f0; F1 f1; F2 f2; F3 f3; F4 f4; F5 f5; F6 f6;
	T1 t1; T2 t2; T3 t3; T4 t4; T5 t5; T6 t6;
}

template<class P, class T1 = int, class T2 = int, class T3 = int, class T4 = int, class T5 = int, class T6 = int>
class CTask : public ITask
{
public:
	typedef void (P::*F0)(void*);
	typedef void (P::*F1)(T1, void*);
	typedef void (P::*F2)(T1, T2, void*);
	typedef void (P::*F3)(T1, T2, T3, void*);
	typedef void (P::*F4)(T1, T2, T3, T4, void*);
	typedef void (P::*F5)(T1, T2, T3, T4, T5, void*);
	typedef void (P::*F6)(T1, T2, T3, T4, T5, T6, void*);

	CTask(P *_p, F0 f, int straget) : p(_p), f0(f), f1(0), f2(0), f3(0), f4(0), f5(0), f6(0), ITask(straget) {}
	CTask(P *_p, F1 f, T1 _t1, int straget) : p(_p), f0(0), f1(f), f2(0), f3(0), f4(0), f5(0), f6(0), t1(_t1), ITask(straget) {}
	CTask(P *_p, F2 f, T1 _t1, T2 _t2, int straget) : p(_p), f0(0), f1(0), f2(f), f3(0), f4(0), f5(0), f6(0), t1(_t1), t2(_t2), ITask(straget) {}
	CTask(P *_p, F3 f, T1 _t1, T2 _t2, T3 _t3, int straget) : p(_p), f0(0), f1(0), f2(0), f3(f), f4(0), f5(0), f6(0), t1(_t1), t2(_t2), t3(_t3), ITask(straget) {}
	CTask(P *_p, F4 f, T1 _t1, T2 _t2, T3 _t3, T4 _t4, int straget) : p(_p), f0(0), f1(0), f2(0), f3(0), f4(f), f5(0), f6(0), t1(_t1), t2(_t2), t3(_t3), t4(_t4), ITask(straget) {}
	CTask(P *_p, F5 f, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, int straget) : p(_p), f0(0), f1(0), f2(0), f3(0), f4(0), f5(f), f6(0), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5), ITask(straget) {}
	CTask(P *_p, F6 f, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, int straget) : p(_p), f0(0), f1(0), f2(0), f3(0), f4(0), f5(0), f6(f), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5), t6(_t6), ITask(straget) {}

	void operator ()(void *thread)
	{
		if (f0 && p) {return (p->*f0)(thread);}
		if (f1 && p) {return (p->*f1)(t1, thread);}
		if (f2 && p) {return (p->*f2)(t1, t2, thread);}
		if (f3 && p) {return (p->*f3)(t1, t2, t3, thread);}
		if (f4 && p) {return (p->*f4)(t1, t2, t3, t4, thread);}
		if (f5 && p) {return (p->*f5)(t1, t2, t3, t4, t5, thread);}
		if (f6 && p) {return (p->*f6)(t1, t2, t3, t4, t5, t6, thread);}
	}

private:
	P *p;
	F0 f0; F1 f1; F2 f2; F3 f3; F4 f4; F5 f5; F6 f6;
	T1 t1; T2 t2; T3 t3; T4 t4; T5 t5; T6 t6;
}