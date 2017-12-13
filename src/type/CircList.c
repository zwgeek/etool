#include "CircList.h"


etool_circList* etool_circList_create(const unsigned int typeSize, const unsigned int size)
{
	etool_circList *list = malloc(sizeof(etool_circList));
	if (list == 0) { return 0; }
	list->memory = etool_memory_create(sizeof(struct _etool_circNode) + typeSize, size);
	if (list->memory == 0) { free(list); return 0; }
	list->next = (struct _etool_circNode*)list;
	return list;
}

void etool_circList_destroy(etool_circList *list)
{
	etool_memory_destroy(list->memory);
	free(list);
}

int etool_circList_size(const unsigned int typeSize, const unsigned int size)
{
	return sizeof(etool_circList) + etool_memory_size(sizeof(struct _etool_circNode) + typeSize, size);
}

etool_circList* etool_circList_init(void *block, const unsigned int typeSize, const unsigned int size)
{
	if (block == 0) { return 0; }
	etool_circList *list = block;
	list->memory = etool_memory_init(block + sizeof(etool_circList), typeSize, size);
	list->next = (struct _etool_circNode*)list;
	return list;
}

void etool_circList_clear(etool_circList *list)
{
	etool_memory_clear(list->memory);
	list->next = (struct _etool_circNode*)list;
}

int etool_circList_length(etool_circList *list)
{
	return list->memory->length;
}

int etool_circList_empty(etool_circList *list)
{
	return list->next == (struct _etool_circNode*)list;
}

int etool_circList_full(etool_circList *list)
{
	return list->memory->length == list->memory->size;
}

void* etool_circList_find(etool_circList *list, unsigned int index)
{
	if (index >= list->memory->length) { return 0; }
	struct _etool_circNode *node = list->next;
	while(index > 0) {
		index--;
		node = node->next;
	}
	return node->data;
}

int etool_circList_locate(etool_circList *list, void *value)
{
	int n, index = 0, isFind = 0;
	struct _etool_circNode *node = list->next;
	while(node != 0) {
		if (node->data[0] == ((unsigned char*)value)[0]) {
			isFind = 1;
			for (n = 1; n <= list->memory->typeSize; n++) {
				if (node->data[n] != ((unsigned char*)value)[n]) {
					isFind = 0;
					break;
				}
			}
		}
		if (isFind) {
			return index;
		}
		index++;
		node = node->next;
	}
	return -1;
}

int etool_circList_insert(etool_circList *list, unsigned int index, void *value)
{
	if (index > list->memory->length) {
		return -1;
	}
	struct _etool_circNode *newNode = etool_memory_malloc(list->memory);
	if (newNode == 0) { return -1; }
	newNode->data = (void*)newNode + sizeof(struct _etool_circNode);
	int n;
	for (n = 0; n < list->memory->typeSize; n++) {
		newNode->data[n] = ((unsigned char*)value)[n];
	}

	//建立在list可以和node互转
	struct _etool_circNode *node = (struct _etool_circNode*)list;
	index--;
	while(index > 0) {
		index--;
		node = node->next;
	}
	newNode->next = node->next;
	node->next = newNode;
	return 0;
}

int etool_circList_erase(etool_circList *list, unsigned int index, void *value)
{
	if (index >= list->memory->length) {
		return -1;
	}
	int n;
	//建立在list可以和node互转
	struct _etool_circNode *node = (struct _etool_circNode*)list;
	index--;
	while(index > 0) {
		index--;
		node = node->next;
	}
	struct _etool_circNode *_node = node->next;
	node->next = _node->next;
	for (n = 0; n < list->memory->typeSize; n++) {
		((unsigned char*)value)[n] = _node->data[n];
	}
	etool_memory_free(list->memory, _node);
	return 0;
}

int etool_circList_copy(etool_circList *srcList, etool_circList *dstList)
{
	if (srcList->memory->typeSize != dstList->memory->typeSize) {
		return -1;
	}
	struct _etool_circNode *srcNode = (struct _etool_circNode*)srcList;
	struct _etool_circNode *dstNode = (struct _etool_circNode*)dstList;
	etool_memory_clear(dstList->memory);
	//开始拷贝
	int n;
	struct _etool_circNode *newNode = 0;
	while (srcNode->next != 0) {
		newNode = etool_memory_malloc(dstList->memory);
		if (newNode == 0) { return -1; }
		newNode->data = (void*)newNode + sizeof(struct _etool_circNode);
		for (n = 0; n < srcList->memory->typeSize; n++) {
			newNode->data[n] = srcNode->data[n];
		}
		dstNode->next = newNode;
		dstNode = newNode;
		srcNode = srcNode->next;
	}
	dstNode->next = (struct _etool_circNode*)dstList;
	return 0;
}

etool_circListIterator* etool_circListIterator_init(etool_circList *list)
{
	if (list->next == (struct _etool_circNode*)list) { return 0; }
	etool_circListIterator *iterator = malloc(sizeof(etool_circListIterator));
	if (iterator == 0) { return 0; }
	iterator->data = list->next->data;
	iterator->list = (struct _etool_circNode*)list;
	iterator->next = list->next->next;
	return iterator;
}

int etool_circListIterator_next(etool_circListIterator *iterator)
{
	if (iterator->next == iterator->list) {
		free(iterator);
		return 0;
	}
	iterator->data = iterator->next->data;
	iterator->next = iterator->next->next;
	return 1;
}