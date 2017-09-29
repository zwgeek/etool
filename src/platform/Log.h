/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 日志
 */

#ifndef ETOOL_PLATFORM_LOG
#define ETOOL_PLATFORM_LOG

namespace etool {

#include <stdio.h>
#include <string>
#if defined(_windows)
#endif

#if defined(_linux) || defined(_mac)
#endif

#if defined(_android)
#endif

#if defined(_ios)
#endif

enum LogLevel {
	VERBOSE = 0,
	DEBUG,
	INFO,
	WARN,
	ERROR
};
enum LogMode {
	COMMON = 0,		//普通
	LOOP,			//双循环
	TIME			//时间
};

class CLog
{
	CLog() {}
	CLog(const CLog&) {}
	CLog& operator=(const CLog&) { return *this; }
	~CLog() {}

public:
	static void initLogPath(const std::string&, unsigned int level = 0, unsigned int mode = 0);
	inline static void changeLevel(unsigned int level) { m_level = level; }
	static void addLog(const std::string&, ...)

private:
	static FILF *m_file;
	static std::string m_path;
	static unsigned int m_level;
	static unsigned int m_mode;
};

} //etool
#endif //ETOOL_PLATFORM_LOG