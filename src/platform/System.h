/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 系统类: 一些常用的工具使用
 */

#ifndef ETOOL_PLATFORM_SYSTEM
#define ETOOL_PLATFORM_SYSTEM

#if defined(_windows)
#include <windows.h>		
#endif
#if defined(_android) || defined(_linux)
#include <system.h>	
#endif
#if defined(_mac) || defined(_ios)
#include <sys/time.h>
#endif

namespace etool {

// struct SystemInterior;

class CSystem
{
	CSystem() {}
	~CSystem() {}
	CSystem(const CSystem&) {}
	CSystem& operator=(const CSystem&) { return *this; }

public:
	static void sleep(unsigned long milliseconds);

};
} //etool
#endif //ETOOL_PLATFORM_SYSTEM
