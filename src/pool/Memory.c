#include "Memory.h"


etool_memory* etool_memory_create(const unsigned int typeSize, const unsigned int size)
{
	etool_memory *memory = malloc(sizeof(etool_memory));
	if (memory == 0) { return 0; }
	unsigned char *data = malloc(typeSize * size);
	if (data == 0) { free(memory); return 0; }
	memory->freeAddr = (unsigned char**)malloc(sizeof(void*) * size);
	if (memory->freeAddr == 0) { free(memory); free(data); return 0; }
	int n;
	for (n = 0; n < size; n++) {
		memory->freeAddr[n] = data + n * typeSize;
	}
	memory->typeSize = typeSize;
	memory->size = size;
	memory->length = 0;
	memory->mode = size;
	return memory;
}

void etool_memory_destroy(etool_memory *memory)
{
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
	memory->mode = ETOOL_MODE_INIT;
	return memory;
}

void etool_memory_clear(etool_memory *memory)
{
	memory->length = 0;
}

void* etool_memory_malloc(etool_memory *memory)
{
	if (memory->length == memory->size) {
		if (memory->mode > ETOOL_MODE_INIT) {
			ETOOL_MEMORY_EXTEND(memory);
		} else {
			return 0;
		}
	}
	memory->length++;
	return memory->freeAddr[memory->length - 1];
}

int etool_memory_free(etool_memory *memory, void *node)
{
	if (memory->length == 0) { return -1; }
	memory->length--;
	memory->freeAddr[memory->length] = node;
	return 0;
}