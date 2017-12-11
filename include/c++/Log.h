/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 日志
 */

#ifndef ETOOL_LOG
#define ETOOL_LOG

#define VERBOSE(fmt, ...) g_log.printf(ETOOL_LOG_VERBOSE, "__FILE__:__FUNCTION__:%05d--verbose: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define DEBUG(fmt, ...)   g_log.printf(ETOOL_LOG_DEBUG, "__FILE__:__FUNCTION__:%05d--debug: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define INFO(fmt, ...)    g_log.printf(ETOOL_LOG_INFO, "__FILE__:__FUNCTION__:%05d--info: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define WARN(fmt, ...)    g_log.printf(ETOOL_LOG_WARN, "__FILE__:__FUNCTION__:%05d--warn: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define ERR(fmt, ...)     g_log.printf(ETOOL_LOG_ERR, "__FILE__:__FUNCTION__:%05d--err: "fmt"\n", __LINE__, ##__VA_ARGS__)
#define FATAL(fmt, ...)   g_log.printf(ETOOL_LOG_FATAL, "__FILE__:__FUNCTION__:%05d--fatal: "fmt"\n", __LINE__, ##__VA_ARGS__)

typedef enum _etool_logLevel {
	ETOOL_LOG_VERBOSE = 0,
	ETOOL_LOG_DEBUG,
	ETOOL_LOG_INFO,
	ETOOL_LOG_WARN,
	ETOOL_LOG_ERR,
	ETOOL_LOG_FATAL
} etool_logLevel;

typedef struct _etool_log etool_log;
namespace etool {

class CLog {
	CLog(const CLog &log) { this->m_log = log.m_log; }
	CLog& operator=(const CLog &log) { this->m_log = log.m_log; return *this; }

public:
	CLog(const char *path = "./", const etool_logLevel level = ETOOL_LOG_DEBUG) { m_log = etool_log_create(path, level); }
	~CLog() { etool_log_destroy(m_log); }

	inline  int setPath(const char *path) { return etool_log_path(m_log, path); }
	inline void setLevel(const etool_logLevel level) { etool_log_level(m_log, level); }
	inline void flush() { etool_log_flush(m_log); }
	inline void printf(const etool_logLevel level, const char *fmt, ...) { etool_log_printf(m_log, level, ...); }
	inline void asyncPrintf(const etool_logLevel level, const char *fmt, ...) { etool_log_async_printf(m_log, level, ...); }

private:
	etool_log *m_log;
};
} //etool

//声明一个log,跟宏搭配使用,建议这种用法
extern CLog g_log;
#endif //ETOOL_LOG