#include "Memory.h"


etool_memory* etool_memory_create(const unsigned int typeSize, const unsigned int size)
{
	etool_memory *memory = malloc(sizeof(etool_memory));
	if (memory == 0) { return 0; }
	unsigned char *data = malloc(typeSize * size);
	if (data == 0) { free(memory); return 0; }
	memory->freeAddr = malloc(sizeof(void*) * (size + 1));
	if (memory->freeAddr == 0) { free(memory); free(data); return 0; }
	int n;
	for (n = 0; n < size; n++) {
		memory->freeAddr[n] = data + n * typeSize;
	}
	memory->freeAddr[size] = data;
	memory->typeSize = typeSize;
	memory->size = size;
	memory->length = 0;
	memory->mode = ETOOL_MEMORY_MODE_CREATE;
	return memory;
}

void etool_memory_destroy(etool_memory *memory)
{
	int n;
	for (n = 0; n < memory->mode; n++) {
		free(memory->freeAddr[memory->size + n]);
	}
	free(memory);
}

int etool_memory_size(const unsigned int typeSize, const unsigned int size)
{
	return sizeof(etool_memory) + typeSize * size + sizeof(void*) * size;
}

etool_memory* etool_memory_init(void *block, const unsigned int typeSize, const unsigned int size)
{
	if (block == 0) { return 0; }
	int n;
	etool_memory *memory = block;
	unsigned char *data = block + sizeof(etool_memory);
	memory->freeAddr = block + sizeof(etool_memory) + typeSize * size;
	for (n = 0; n < size; n++) {
		memory->freeAddr[n] = data + n * typeSize;
	}
	memory->typeSize = typeSize;
	memory->size = size;
	memory->length = 0;
	memory->mode = ETOOL_MEMORY_MODE_INIT;
	return memory;
}

void etool_memory_clear(etool_memory *memory)
{
	int n, m, offset = 0;
	unsigned char *data;
	for (n = 0; n < memory->mode; n++) {
		data = memory->freeAddr[memory->size + n];
		for (m = 0; m < (memory->size / memory->mode); m++) {
			memory->freeAddr[offset + m] = data + m * memory->typeSize;
		}
		offset = offset + memory->size / memory->mode;
	}
	memory->length = 0;
}

void* etool_memory_malloc(etool_memory *memory)
{
	if (memory->length == memory->size) {
		if (memory->mode != ETOOL_MEMORY_MODE_INIT) {
			ETOOL_MEMORY_EXTEND(memory);
		} else {
			return 0;
		}
	}
	return memory->freeAddr[memory->length++];
}

int etool_memory_free(etool_memory *memory, void *node)
{
	if (memory->length == 0) { return -1; }
	memory->freeAddr[--memory->length] = node;
	return 0;
}