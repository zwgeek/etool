#include "SeqList.h"


int etool_seqList_create(etool_seqList *list, unsigned int typeSize, unsigned int size)
{
	list->data = malloc(typeSize * size);
	if (list->data == 0) { return -1; }
	list->typeSize = typeSize;
	list->size = size;
	list->length = 0;
	return 0;
}

void etool_seqList_destroy(etool_seqList *list)
{
	free(list->data);
}

int etool_seqList_init(etool_seqList *list, unsigned int typeSize, void *data, unsigned int size)
{
	if (data == 0) { return -1; }
	list->data = data;
	list->typeSize = typeSize;
	list->size = size;
	list->length = 0;
	return 0;
}

int etool_seqList_clear(etool_seqList *list)
{
	list->length = 0;
	return 0;
}

int etool_seqList_length(etool_seqList *list)
{
	return list->length;
}

int etool_seqList_empty(etool_seqList *list)
{
	//1为真, 0为假
	return (list->length == 0) ? 1 : 0;
}

int etool_seqList_full(etool_seqList *list)
{
	//1为真, 0为假
	return (list->length == list->size) ? 1 : 0;
}

void* etool_seqList_find(etool_seqList *list, int index)
{
	int offset = index * list->typeSize;
	return list->data + offset;
}

int etool_seqList_locate(etool_seqList *list, void *node)
{
	int offset = 0, isFind = 0;
	while (offset < list->length) {
		if (list->data[offset] == ((unsigned char*)node)[0]) {
			isFind = 1;
			for (int n = 1; n < list->typeSize; n++) {
				offset++;
				if (list->data[offset] != ((unsigned char*)node)[n]) {
					isFind = 0;
					offset = offset - n;
					break;
				}
			}
		}
		if (isFind) {
			return offset / list->typeSize - 1;
		}
		offset += list->typeSize;
	}
	return -1;
}

int etool_seqList_insert(etool_seqList *list, unsigned int index, void *node)
{
	if (list->length == list->size) {
		return -1;
	}
	if (index < 0 || index > list->length) {
		return -1;
	}
	//依次后移,空出第index位置
	int offset = list->length * list->typeSize - 1;
	while (offset >= index * list->typeSize) {
		list->data[offset + list->typeSize] = list->data[offset];
		offset--;
	}
	offset++;
	for (int n = 0; n < list->typeSize; n++) {
		list->data[offset + n] = ((unsigned char*)node)[n];
	}
	list->length++;
	return 0;
}

int etool_seqList_erase(etool_seqList *list, unsigned int index, void *node)
{
	if (list->length == 0) {
		return -1;
	}
	if (index < 0 || index >= list->length) {
		return -1;
	}
	int offset = index * list->typeSize;
	if (node != 0) {
		for (int n = 0; n < list->typeSize; n++) {
			((unsigned char*)node)[n] = list->data[offset + n];
		}
	}
	while (offset <= list->length * list->typeSize - 1) {
		list->data[offset] = list->data[offset + list->typeSize];
		offset++;
	}
	list->length--;
	return 0;
}

int etool_seqList_extend()
{
	return 0;
}