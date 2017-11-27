#if defined(_windows)
#include <windows.h>
#include <wincon.h>
#define BOLD FOREGROUND_INTENSITY
#define RED FOREGROUND_RED
#define CYAN FOREGROUND_GREEN | FOREGROUND_BLUE
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define MAGENTA FOREGROUND_RED | FOREGROUND_BLUE
const WORD colors[6] = { CYAN, CYAN, WHITE | BOLD, YELLOW | BOLD, RED | BOLD , MAGENTA | BOLD };

#define ETOOL_LOG_STDOUT(msg) \
fwrite(msg, sizeof(char), strlen(msg), stdout)

#define ETOOL_LOG_COLOR_STDOUT(msg) \
CONSOLE_SCREEN_BUFFER_INFO origBufferInfo; \
HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE); \
GetConsoleScreenBufferInfo(outHandle, &origBufferInfo); \
SetConsoleTextAttribute(outHandle, colors[level]); \
WriteConsoleA(outHandle, msg, (DWORD)strlen(msg), NULL, NULL); \
SetConsoleTextAttribute(outHandle, origBufferInfo.wAttributes)
#endif

#if defined(_linux) || defined(_mac) || defined(_ios)
#define RESET "\033[00m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define RED_BOLD "\033[31m\033[1m"
#define CYAN "\033[36m"
#define CYAN_BOLD "\033[36m\033[1m"
#define WHITE "\033[37m"
#define WHITE_BOLD "\033[37m\033[1m"
#define YELLOW "\033[33m"
#define YELLOW_BOLD "\033[33m\033[1m"
#define MAGENTA "\033[35m"
#define MAGENTA_BOLD "\033[35m\033[1m"
const char *colors[6] = { CYAN, CYAN, WHITE_BOLD, YELLOW_BOLD, RED_BOLD,  MAGENTA_BOLD };

#define ETOOL_LOG_STDOUT(msg) \
fwrite(msg, sizeof(char), strlen(msg), stdout)

#define ETOOL_LOG_COLOR_STDOUT(msg) \
fwrite(colors[level], sizeof(char), strlen(colors[level]), stdout); \
fwrite(msg, sizeof(char), strlen(msg), stdout); \
fwrite(RESET, sizeof(char), strlen(RESET), stdout)
#endif

#if defined(_android)
#include <android/log.h>
const android_LogPriority colors[6] = { ANDROID_LOG_VERBOSE, ANDROID_LOG_DEBUG, ANDROID_LOG_INFO, ANDROID_LOG_WARN, ANDROID_LOG_ERROR, ANDROID_LOG_FATAL };

#define ETOOL_LOG_STDOUT(msg) \
__android_log_write(colors[level], "etool", msg)

#define ETOOL_LOG_COLOR_STDOUT(msg) \
__android_log_write(colors[level], "etool", msg)
#endif
