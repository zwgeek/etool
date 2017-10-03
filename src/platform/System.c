#include "System.h"


void etool_system_sleep(unsigned long milliseconds)
{
#if defined(_windows)
	Sleep(milliseconds);
#endif

#if defined(_linux) || defined(_android)
	usleep(milliseconds * 1000);
#endif

#if defined(_mac) || defined(_ios)
	sleep(milliseconds * 1000);
#endif
}
