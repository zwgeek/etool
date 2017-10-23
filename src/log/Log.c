// #include "Log.h"
// #include "../platform/Mutex.h"


// FILF *g_file = 0;
// char g_path[128] = {0};
// unsigned int g_level;
// unsigned int g_mode;
// etool_mutex g_path_mutex = MUTEX_NULL;
// etool_mutex g_msg_mutex = MUTEX_NULL;


// int etool_log_open(const char *path, unsigned int level, unsigned int mode)
// {
// 	strcpy(g_path, path);
// 	g_level = level;
// 	g_mode = mode;
// 	int ret;
// 	if (g_path_mutex == MUTEX_NULL) {
// 		ret = etool_mutex_create(&g_path_mutex);
// 		if (ret != 0) {
// 			return ret;
// 		}
// 	}
// 	if (g_msg_mutex == MUTEX_NULL) {
// 		ret = etool_mutex_create(&g_msg_mutex);
// 		if (ret != 0) {
// 			etool_mutex_destroy(&g_path_mutex);
// 			g_path_mutex = MUTEX_NULL
// 			return ret;
// 		}
// 	}	
	
// 	if (g_file == 0) {
// 		if (mode == etool_logMode.LOOP) {
// 			strcat(g_path, "_1");
// 		}
// 		g_file = fopen(path, "rw+");
// 	}
// 	if (g_file == 0) {
// 		etool_mutex_destroy(&g_path_mutex);
// 		g_path_mutex = MUTEX_NULL
// 		etool_mutex_destroy(&g_msg_mutex);
// 		g_msg_mutex = MUTEX_NULL
// 		return -1;
// 	}
// }

// void etool_log_close()
// {
// 	etool_mutex_lock(&g_msg_mutex);

// 	etool_mutex_unlock(&g_msg_mutex);
// 	if (g_path_mutex != MUTEX_NULL) {
// 		etool_mutex_destroy(&g_path_mutex);
// 		g_path_mutex = MUTEX_NULL
// 	}
// 	if (g_msg_mutex != MUTEX_NULL) {
// 		etool_mutex_destroy(&g_msg_mutex);
// 		g_msg_mutex = MUTEX_NULL
// 	}
// 	if (g_file != 0) {
// 		fclose(g_file);
// 		g_file = 0;
// 	}
// }

// void etool_log_path(const char *path)
// {
// 	strcpy(g_path, path);
// }

// void etool_log_level(unsigned int level)
// {
// 	g_level = level; 
// }

// void etool_log_mode(unsigned int mode)
// {
// 	g_mode = mode;
// }

// void etool_log_printf(enum etool_logLevel level, const char *fmt, ...)
// {
// 	//选择使用模式
// 	switch (mode)
// 	{
// 	case LogMode.COMMON :
// 		break;
// 	case LogMode.LOOP :
// 		break;
// 	case LogMode.TIME :
// 		break;
// 	default :
// 		break;
// 	}
// 	m_path = path;
	
// 	m_level = level;
// 	m_mode = mode;
// }
