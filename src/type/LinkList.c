#include "LinkList.h"


etool_linkList* etool_linkList_create(const unsigned int typeSize, const unsigned int size)
{
	etool_linkList *list = malloc(sizeof(etool_linkList));
	if (list == 0) { return 0; }
	list->memory = etool_memory_create(sizeof(struct _etool_linkNode) + typeSize, size);
	if (list->memory == 0) { free(list); return 0; }
	list->next = 0;
	return list;
}

void etool_linkList_destroy(etool_linkList *list)
{
	etool_memory_destroy(list->memory);
	free(list);
}

int etool_linkList_size(const unsigned int typeSize, const unsigned int size)
{
	return sizeof(etool_linkList) + etool_memory_size(sizeof(struct _etool_linkNode) + typeSize, size);
}

etool_linkList* etool_linkList_init(void *block, const unsigned int typeSize, const unsigned int size)
{
	if (block == 0) { return 0; }
	etool_linkList *list = block;
	list->memory = etool_memory_init(block + sizeof(etool_linkList), typeSize, size);
	list->next = 0;
	return list;
}

void etool_linkList_clear(etool_linkList *list)
{
	etool_memory_clear(list->memory);
	list->next = 0;
}

int etool_linkList_length(etool_linkList *list)
{
	return list->memory->length;
}

int etool_linkList_empty(etool_linkList *list)
{
	return list->next == 0;
}

int etool_linkList_full(etool_linkList *list)
{
	return list->memory->length == list->memory->size;
}

void* etool_linkList_find(etool_linkList *list, unsigned int index)
{
	if (index >= list->memory->length) { return 0; }
	struct _etool_linkNode *node = list->next;
	while(index > 0) {
		index--;
		node = node->next;
	}
	return node->data;
}

int etool_linkList_locate(etool_linkList *list, void *value)
{
	struct _etool_linkNode *node = list->next;
	int n, index = 0, isFind = 0;
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

int etool_linkList_insert(etool_linkList *list, unsigned int index, void *value)
{
	if (index > list->memory->length) {
		return -1;
	}
	struct _etool_linkNode *newNode = etool_memory_malloc(list->memory);
	if (newNode == 0) { return -1; }
	int n;
	newNode->data = (void*)newNode + sizeof(struct _etool_linkNode);
	for (n = 0; n < list->memory->typeSize; n++) {
		newNode->data[n] = ((unsigned char*)value)[n];
	}

	//建立在list可以和node互转
	struct _etool_linkNode *node = (struct _etool_linkNode*)list;
	while(index > 0) {
		index--;
		node = node->next;
	}
	newNode->next = node->next;
	node->next = newNode;
	return 0;
}

int etool_linkList_erase(etool_linkList *list, unsigned int index, void *value)
{
	if (index >= list->memory->length) {
		return -1;
	}
	//建立在list可以和node互转
	int n;
	struct _etool_linkNode *node = (struct _etool_linkNode*)list;
	while(index > 0) {
		index--;
		node = node->next;
	}
	struct _etool_linkNode *_node = node->next;
	node->next = _node->next;
	for (n = 0; n < list->memory->typeSize; n++) {
		((unsigned char*)value)[n] = _node->data[n];
	}
	etool_memory_free(list->memory, _node);
	return 0;
}

int etool_linkList_copy(etool_linkList *srcList, etool_linkList *dstList)
{
	if (srcList->memory->typeSize != dstList->memory->typeSize) {
		return -1;
	}
	struct _etool_linkNode *srcNode = (struct _etool_linkNode*)srcList;
	struct _etool_linkNode *dstNode = (struct _etool_linkNode*)dstList;
	etool_memory_clear(dstList->memory);
	//开始拷贝
	int n;
	struct _etool_linkNode *newNode = 0;
	while (srcNode->next != 0) {
		newNode = etool_memory_malloc(dstList->memory);
		if (newNode == 0) { return -1; }
		newNode->data = (void*)newNode + sizeof(struct _etool_linkNode);
		for (n = 0; n < srcList->memory->typeSize; n++) {
			newNode->data[n] = srcNode->data[n];
		}
		dstNode->next = newNode;
		dstNode = newNode;
		srcNode = srcNode->next;
	}
	dstNode->next = 0;
	return 0;
}

etool_linkListIterator* etool_linkListIterator_init(etool_linkList *list)
{
	if (list->next == 0) { return 0; }
	etool_linkListIterator *iterator = malloc(sizeof(etool_linkListIterator));
	if (iterator == 0) { return 0; }
	iterator->data = list->next->data;
	iterator->next = list->next->next;
	return iterator;
}

int etool_linkListIterator_next(etool_linkListIterator *iterator)
{
	if (iterator->next == 0) {
		free(iterator);
		return 0;
	}
	iterator->data = iterator->next->data;
	iterator->next = iterator->next->next;
	return 1;
}