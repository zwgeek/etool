// /**
//  * Copyright 2017, PaPa.  All rights reserved.
//  * 原子计数器
//  */

// #ifndef ETOOL_PLATFORM_ATOMICCOUNT
// #define ETOOL_PLATFORM_ATOMICCOUNT

// #if defined(_windows)
// #include <windows.h>
// #endif
// #if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
// #include <system.h>
// #endif

// namespace etool {

// class CAtomicCount
// {
// 	CAtomicCount(const CSystem&) {}
// 	CSystem& CAtomicCount=(const CSystem&) { return *this; }

// public:
// 	CAtomicCount() {}
// 	~CAtomicCount() {}
// 	void sleep(unsigned long milliseconds);

// };
// } //etool
// #endif //ETOOL_PLATFORM_ATOMICCOUNT
