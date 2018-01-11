extern "C" {
#include "../src/platform/System.h"
#include "../src/platform/Thread.h"
}

void testProc(void *self)
{
	// etool_thread *thread = (etool_thread*)self;
	// while (etool_thread_loop(thread)) {
	// 	// for (int i = 1; i < 100; i++)
	// 	// 	printf("curID : %ld\n", 1);
	// 	// break;
	// }
}

int type_thread_test()
{
	etool_thread *threads[10];
	for (int i = 0; i < 10; i++) {
		threads[i] = etool_thread_create();
		etool_thread_start(threads[i], testProc, threads[i]);
		break;
	}

	etool_os_sleep(10000);
	return 0;
}