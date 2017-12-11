/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于块分配的内存(管理)模块
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_MEMORY
#define ETOOL_MEMORY

typedef struct _etool_memory etool_memory;
namespace etool {

class CMemory {
	CMemory(const CMemory &memory) { this->m_memory = memory.m_memory; }
	CMemory& operator=(const CMemory &memory) { this->m_memory = memory.m_memory; return *this; }

public:
	CMemory(const unsigned int typeSize, const unsigned int size) : m_memory(etool_memory_create(typeSize, size)) {}
	~CMemory() { etool_memory_destroy(m_memory); }

	inline void  clear() { etool_memory_clear(m_memory); }
	inline void* malloc() { etool_memory_malloc(m_memory); }
	inline int free(void *node) { etool_memory_free(m_memory, node); }

private:
	etool_memory *m_memory;
};
} //etool
#endif //ETOOL_MEMORY