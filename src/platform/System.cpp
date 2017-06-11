#include "System.h"

namespace etool {

void CSystem::sleep(unsigned long milliseconds)
{
#if defined(_windows)
	Sleep(milliseconds);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	usleep(milliseconds * 1000);
#endif
}

} //etool
