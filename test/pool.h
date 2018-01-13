extern "C" {
#include "../src/pool/Executor.h"
}

void wProc(void *param)
{
	int *index = (int*)param;
	printf("curID : %ld, %d\n", etool_thread_getCurrentID(), *index);	
}

int pool_executor_test()
{
	etool_executor *executor = etool_executor_create(1, 3);
	for (int i = 0; i < 100; i++) {
		 etool_executor_work(executor, wProc, &i, i % 3);
	}
	system("pause");
	etool_executor_destroy(executor);

	return 0;
}