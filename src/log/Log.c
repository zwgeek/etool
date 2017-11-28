#include "Log.h"


void etool_log_threadPorc(void *this)
{
	etool_log *log = (etool_log*)this;
	char *msg;
	while(etool_thread_loop(&(log->thread))) {
		etool_mutexEx_lock(&(log->mutex));
		if (etool_circQueue_exit(log->queue, (void*)&msg) == -1) {
			etool_condition_wait(&(log->condition), &(log->mutex));
		}
#ifdef USE_LOG_STDOUT
		ETOOL_LOG_STDOUT(msg);
#endif
#ifdef USE_LOG_COLOR_STDOUT
		ETOOL_LOG_COLOR_STDOUT(log->level, msg);
#endif
		fwrite(msg, sizeof(char), strlen(msg), log->file);
		etool_mutexEx_unlock(&(log->mutex));
		free(msg);
	}
}

etool_log* etool_log_create(const char *path, const etool_logLevel level)
{
	etool_log *log = malloc(sizeof(etool_log));
	if (log == 0) { return 0; }
	log->file = fopen(path, "rw+");
	if (log->file == 0) {
		free(log);
		return 0;
	}
	strcpy(log->path, path);
	log->level = level;
	log->queue = etool_circQueue_create(sizeof(char*), ETOOL_LOG_QUEUE_SIZE);
	etool_mutexEx_load(&(log->mutex));
	etool_condition_load(&(log->condition));
	etool_thread_load(&(log->thread));
	etool_thread_start(&(log->thread), etool_log_threadPorc, log);
	return log;
}

void etool_log_destroy(etool_log *log)
{
	etool_thread_end(&(log->thread));
	fclose(log->file);
	etool_circQueue_destroy(log->queue);
	etool_mutexEx_unload(&(log->mutex));
	etool_condition_unload(&(log->condition));
	etool_thread_unload(&(log->thread));
	free(log);
}

int etool_log_path(etool_log *log, const char *path)
{	
	FILE *file = fopen(path, "rw+");
	if (file == 0) {
		return -1;
	}
	strcpy(log->path, path);
	FILE *tmpFile = log->file;
	log->file = file;
	fclose(tmpFile);
	return 0;
}

void etool_log_level(etool_log *log, const etool_logLevel level)
{
	log->level = level;
}

void etool_log_flush(etool_log *log)
{
	fflush(log->file);
}

//const char *fileName, const int lineNum, const char *functionName
void etool_log_printf(etool_log *log, etool_logLevel level, const char *fmt, ...)
{
	if (level > log->level) {
		return;		
	}
	char msg[ETOOL_LOG_MSG_SIZE];
	va_list argList;
	va_start(argList, fmt);
	vsprintf(msg, fmt, argList);
	va_end(argList);
#ifdef USE_LOG_STDOUT
	ETOOL_LOG_STDOUT(msg);
#endif
#ifdef USE_LOG_COLOR_STDOUT
	ETOOL_LOG_COLOR_STDOUT(level, msg);
#endif
	fwrite(msg, sizeof(char), strlen(msg), log->file);
}

void etool_log_async_printf(etool_log *log, etool_logLevel level, const char *fmt, ...)
{
	if (level > log->level) {
		return;		
	}
	char *msg = malloc(sizeof(char) * ETOOL_LOG_MSG_SIZE);
	va_list argList;
	va_start(argList, fmt);
	vsprintf(msg, fmt, argList);
	va_end(argList);
	etool_mutexEx_lock(&(log->mutex));
	if (etool_circQueue_empty(log->queue)) {
		etool_condition_signal(&(log->condition));
	}
	etool_circQueue_enter(log->queue, (void*)&msg);
	etool_mutexEx_unlock(&(log->mutex));
}