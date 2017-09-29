#include "Log.h"

namespace etool {

FILF *CLog::m_file = 0;
std::string CLog::m_path;
unsigned int CLog::m_level = 0;
unsigned int CLog::m_mode = 0;

void CLog::initLogPath(const std::string &path, unsigned int level = 0, unsigned int mode = 0)
{
	//选择使用模式
	switch (mode)
	{
	case LogMode.COMMON :
		break;
	case LogMode.LOOP :
		break;
	case LogMode.TIME :
		break;
	default :
		break;
	}
	m_path = path;
	m_file = fopen(m_path, "w+");
	m_level = level;
	m_mode = mode;
}

void CLog::addLog(const std::string &content, ...)
{

}
} //etool
