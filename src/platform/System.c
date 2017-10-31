#include "System.h"


void etool_os_sleep(const unsigned long milliseconds)
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

int etool_dir_exist(const char *path)
{
	return access(path, F_OK);
}

#if defined(_windows)
#define _MKDIR_(path) mkdir(path)
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#define _MKDIR_(path)  mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO)
#endif
int etool_dir_create(const char *path)
{
	char _path[128];
	strcpy(_path, path);
	int length = strlen(_path);
	if (_path[length - 1] != '/') {
		_path[length] = '/';
		_path[length + 1] = 0;
		length++;
	}

	for (int index = 1; index < length; index++) {
		if (_path[index] == '/') {
			_path[index] = 0;
			//access(_path, F_OK) != 0
			if (access(_path, F_OK)) {
				if (_MKDIR_(_path) == -1) {
					return -1;
				}
			}
			_path[index] = '/';
		}
	}
	return 0;
}

int etool_dir_delete(const char *path)
{
	return rmdir(path);
}
