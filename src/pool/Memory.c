#include "Memory.h"


etool_memory* etool_memory_create(unsigned int typeSize, unsigned int size)
{
	etool_memory *memory = malloc(sizeof(etool_memory));
	if (memory == 0) { return 0; }
	memory->data = malloc(typeSize * size + sizeof(void*) * size);
	if (memory->data == 0) { return 0; }
	memory->freeAddr = (unsigned char**)(memory->data + typeSize * size);
	for (int n = 0; n < memory->size; n++) {
		memory->freeAddr[n] = memory->data + n * typeSize;
	}
	memory->typeSize = typeSize;
	memory->size = size;
	memory->length = 0;
	memory->mode = ETOOL_MODE_CREATE;
	return memory;
}

void etool_memory_destroy(etool_memory *memory)
{
	free(memory->data);
	free(memory);
}

int etool_memory_size(unsigned int typeSize, unsigned int size)
{
	return sizeof(etool_memory) + typeSize * size + sizeof(void*) * size;
}

etool_memory* etool_memory_init(void *block, unsigned int typeSize, unsigned int size)
{
	if (block == 0) { return 0; }
	etool_memory *memory = block;
	memory->data = block + sizeof(etool_memory);
	memory->freeAddr = block + sizeof(etool_memory) + typeSize * size;
	for (int n = 0; n < memory->size; n++) {
		memory->freeAddr[n] = memory->data + n * typeSize;
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
		switch (memory->mode) {
		case ETOOL_MODE_CREATE :
			{ ETOOL_MEMORY_EXTEND(memory); }
			break;
		case ETOOL_MODE_INIT :
			return 0;
		default :
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