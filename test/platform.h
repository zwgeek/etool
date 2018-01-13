extern "C" {
#include "../src/platform/System.h"
#include "../src/platform/Thread.h"
#include "../src/platform/Atomic.h"
#include "../src/platform/Mutex.h"
#include "../src/platform/MutexEx.h"
#include "../src/platform/Condition.h"
#include "../src/platform/RecursiveMutex.h"
#include "../src/platform/Semaphore.h"
#include "../src/platform/ReadWriteMutex.h"
}

etool_mutex *mutex;
etool_mutexEx *mutexEx;
etool_condition *condition;
etool_recursiveMutex *recursiveMutex;
etool_semaphore *semaphore;
void testProc(void *self)
{
	etool_thread *thread = (etool_thread*)self;
	while (etool_thread_loop(thread)) {
		// etool_mutex_lock(mutex);
		// etool_mutexEx_lock(mutexEx);
		// etool_recursiveMutex_lock(recursiveMutex);
		etool_semaphore_pend(semaphore);
		for (int i = 0; i < 10; i++) {
			printf("curID : %ld, %p\n", etool_thread_getCurrentID(), thread);	
		}
		// etool_condition_signal(condition);
	}
}

int platform_thread_test()
{
	mutex = etool_mutex_create();
	mutexEx = etool_mutexEx_create();
	condition = etool_condition_create();
	
	recursiveMutex = etool_recursiveMutex_create();
	semaphore = etool_semaphore_create(10);

	etool_thread *threads[10];

	// etool_mutex_lock(mutex);
	// etool_mutex_lock(mutex);
	// etool_mutexEx_lock(mutexEx);
	// etool_mutexEx_lock(mutexEx);
	// etool_recursiveMutex_lock(recursiveMutex);
	// etool_recursiveMutex_lock(recursiveMutex);
	for (int i = 0; i < 1; i++) {
		threads[i] = etool_thread_create();
		printf("create thread %p\n", threads[i]);
		etool_thread_start(threads[i], testProc, threads[i]);
	}

	etool_os_sleep(1000);
	for (int i = 0; i < 1; i++) {
		printf("die the thread %d !\n", i);
		// etool_mutex_unlock(mutex);
		// etool_mutexEx_unlock(mutexEx);
		// etool_recursiveMutex_unlock(recursiveMutex);
		// etool_semaphore_post(semaphore);
		etool_thread_destroy(threads[i]);
		// etool_thread_cancel(threads[i]);

	}

	// // condition->waiters++;
	// // printf("condition is running !\n");
	// // // etool_mutexEx_unlock(mutexEx);
	// // // printf("condition is running1 !\n");
	// // // WaitForSingleObject(condition->cond, INFINITE);
	// // SignalObjectAndWait(mutexEx->mutex, condition->cond, INFINITE, FALSE);
	// // printf("condition is running2 !\n");
	// // WaitForSingleObject(mutexEx->mutex, INFINITE);
	// etool_condition_wait(condition, mutexEx);
	printf("thread is die!\n");

	etool_os_sleep(1000);

	return 0;
}

etool_readWriteMutex *readWriteMutex;
void readProc(void *self)
{
	etool_thread *thread = (etool_thread*)self;
	while (etool_thread_loop(thread)) {
		etool_readWriteMutex_lockRead(readWriteMutex);
		printf("read, curID : %ld, %p\n", etool_thread_getCurrentID(), thread);
		etool_readWriteMutex_unlockRead(readWriteMutex);
		etool_os_sleep(100);
	}
}

void writeProc(void *self)
{
	etool_thread *thread = (etool_thread*)self;
	while (etool_thread_loop(thread)) {
		etool_readWriteMutex_lockWrite(readWriteMutex);
		printf("write, curID : %ld, %p\n", etool_thread_getCurrentID(), thread);
		etool_os_sleep(10000);
		etool_readWriteMutex_unlockWrite(readWriteMutex);
		etool_os_sleep(100);
	}
}

int platform_readWriteMutex_test()
{
	etool_thread *threads[10];
	readWriteMutex = etool_readWriteMutex_create();
	for (int i = 0; i < 5; i++) {
		if (i % 2 == 0) {
			threads[i] = etool_thread_create();
			printf("create readthread %p\n", threads[i]);
			etool_thread_start(threads[i], readProc, threads[i]);
		}
	}
	threads[5] = etool_thread_create();
	printf("create writethread %p\n", threads[5]);
	etool_thread_start(threads[5], writeProc, threads[5]);
	system("pause");

	return 0;
}

int platform_system_test()
{
	printf("%ld\n", (long)etool_os_time());
	const char *path = "a";
	int err = etool_dir_exist(path);
	if (err == 0) {
		printf("dir exist : %d !\n", err);
		etool_dir_delete(path);
	} else {
		printf("dir not exist : %d !\n", err);
		etool_dir_create(path);
	}
	return 0;
}

int platform_atomic_test()
{
	etool_atomic *atomic = etool_atomic_create(2);
	printf("%ld\n", *(long*)atomic);
	etool_atomic_inc(atomic);
	printf("inc, %ld\n", *(long*)atomic);
	etool_atomic_dec(atomic);
	printf("dec, %ld\n", *(long*)atomic);
	etool_atomic_add(atomic, 4);
	printf("add 4, %ld\n", *(long*)atomic);
	etool_atomic_sub(atomic, 4);
	printf("sub 4, %ld\n", *(long*)atomic);
	etool_atomic_or(atomic, 4);
	printf("or 4, %ld\n", *(long*)atomic);
	etool_atomic_and(atomic, 4);
	printf("and 4, %ld\n", *(long*)atomic);
	etool_atomic_xor(atomic, 4);
	printf("xor 4, %ld\n", *(long*)atomic);

	return 0;
}