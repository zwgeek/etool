#include "Linklist.h"


etool_linkList* etool_linkList_create(unsigned int typeSize, unsigned int size)
{
	etool_linkList *list = malloc(sizeof(etool_linkList));
	if (list == 0) { return 0; }
	list->memory = etool_memory_create(sizeof(struct _etool_node) + typeSize, size);
	if (list->memory == 0) { return 0; }
	list->next = 0;
	return list;
}

void etool_linkList_destroy(etool_linkList *list)
{
	etool_memory_destroy(list->memory);
	free(list);
}

int etool_linkList_size(unsigned int typeSize, unsigned int size)
{
	return sizeof(etool_linkList) + etool_memory_size(sizeof(struct _etool_node) + typeSize, size);
}

etool_linkList* etool_linkList_init(void *block)
{
	if (block == 0) { return 0; }
	etool_linkList *list = block;
	list->memory = block + sizeof(etool_linkList);
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
	return (list->next == 0) ? 1 : 0;
}

int etool_linkList_full(etool_linkList *list)
{
	return (list->memory->length == list->memory->size) ? 1 : 0;
}

void* etool_linkList_find(etool_linkList *list, int index)
{
	if (index < 0 || index >= list->memory->length) { return 0; }
	struct _etool_node *node = list->next;
	while(index > 0) {
		index--;
		node = node->next;
	}
	return node->data;
}

int etool_linkList_locate(etool_linkList *list, void *value)
{
	struct _etool_node *node = list->next;
	int index = 0, isFind = 0;
	while(node != 0) {
		if (node->data[0] == ((unsigned char*)value)[0]) {
			isFind = 1;
			for (int n = 1; n <= list->memory->typeSize; n++) {
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
	if (index < 0 || index > list->memory->length) {
		return -1;
	}
	void *offset = etool_memory_malloc(list->memory);
	struct _etool_node *newNode = offset;
	if (newNode == 0) { return -1; }
	newNode->data = offset + sizeof(struct _etool_node);
	for (int n = 0; n < list->memory->typeSize; n++) {
		newNode->data[n] = ((unsigned char*)value)[n];
	}
	newNode->next = 0;

	//建立在list可以和node互转
	struct _etool_node *node = (struct _etool_node*)list;
	index--;
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
	if (index < 0 || index >= list->memory->length) {
		return -1;
	}
	//建立在list可以和node互转
	struct _etool_node *node = (struct _etool_node*)list;
	index--;
	while(index > 0) {
		index--;
		node = node->next;
	}
	struct _etool_node *_node = node->next;
	node->next = _node->next;
	for (int n = 0; n < list->memory->typeSize; n++) {
		((unsigned char*)value)[n] = _node->data[n];
	}
	etool_memory_free(list->memory, _node);
	return 0;
}