extern "C" {
#include "../src/platform/System.h"
#include "../src/platform/Thread.h"
}

void testProc(void *self)
{
	etool_thread *thread = (etool_thread*)self;
	while (etool_thread_loop(thread)) {
		for (int i = 0; i < 2; i++) {
			printf("curID : %ld, %p\n", etool_thread_getCurrentID(), thread);
			etool_os_sleep(10);
		}
	}
}

int type_thread_test()
{
	etool_thread *threads[10];
	for (int i = 0; i < 10; i++) {
		threads[i] = etool_thread_create();
		printf("create thread %p\n", threads[i]);
		etool_thread_start(threads[i], testProc, threads[i]);
	}

	for (int i = 0; i < 10; i++) {
		etool_thread_destroy(threads[i]);
	}

	printf("thread is die!\n");

	etool_os_sleep(20000);

	return 0;
}