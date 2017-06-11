/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 日志
 */

#ifndef ETOOL_PLATFORM_LOG
#define ETOOL_PLATFORM_LOG

namespace etool {

#if defined(_windows)

#endif

#if defined(_linux) || defined(_mac)

#endif

#if defined(_android)

#endif

#if defined(_ios)

#endif

struct LogInterior {

};
class CLog
{
	CLog() {}
	CLog(const CLog&) {}
	~CLog() {}

public:
	
};

} //etool
#endif //ETOOL_PLATFORM_LOG