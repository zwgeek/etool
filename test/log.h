extern "C" {
#include "../src/platform/System.h"
#include "../src/log/Log.h"
}

int log_log_test()
{
	etool_log *log = etool_log_create("a.txt", ETOOL_LOG_VERBOSE);
	// etool_log_printf(log, ETOOL_LOG_VERBOSE, "test, %d\n", 1);
	// etool_log_printf(log, ETOOL_LOG_INFO, "test, %d\n", 2);
	// etool_log_printf(log, ETOOL_LOG_ERR, "test, %d\n", 3);
	// etool_log_printf(log, ETOOL_LOG_FATAL, "test, %d\n", 4);
	
	etool_log_async_printf(log, ETOOL_LOG_VERBOSE, "test, %d\n", 1);
	etool_log_async_printf(log, ETOOL_LOG_INFO, "test, %d\n", 2);
	etool_log_async_printf(log, ETOOL_LOG_ERR, "test, %d\n", 3);
	etool_log_async_printf(log, ETOOL_LOG_FATAL, "test, %d\n", 4);

	// system("pause");
	etool_os_sleep(1000);
	etool_log_destroy(log);

	return 0;
}