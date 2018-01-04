/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于链表方式的线性表
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_LINKLIST
#define ETOOL_TYPE_LINKLIST

#include <stdlib.h>
#include "../pool/Memory.h"

typedef struct _etool_linkList {
	etool_memory *memory;
	struct _etool_linkNode *next;
} etool_linkList;

struct _etool_linkNode {
	unsigned char *data;
	struct _etool_linkNode *next;
};


/**
 * etool_linkList* etool_linkList_init(void *block, const unsigned int typeSize, const unsigned int size);
 * 初始化一个list, 并且将一个数据源设入list(动态存储表示),容器数据由开发者创建销毁
 * @param  block    [not null]
 * @param  volume   [not null]
 * @param  type     [not null]
 */
#define etool_linkList_init(list, volume, type) \
do { \
	list = (etool_linkList*)malloc(sizeof(etool_linkList)); \
	if (list != 0) { \
		(list)->memory = etool_memory_create(sizeof(struct _etool_linkNode) + sizeof(type), volume); \
		if ((list)->memory != 0) { \
			(list)->next = 0; \
		} else { \
			free(list); \
			list = 0; \
		} \
	} \
} while(0)


/**
 * void etool_linkList_destroy(etool_linkList *list);
 * 销毁list(动态存储表示)
 * @param  list [not null]
 */
#define etool_linkList_free(list) \
do { \
	etool_memory_destroy((list)->memory); \
	free(list); \
	list = 0; \
} while(0)

/**
 * void etool_linkList_clear(etool_linkList *list);
 * 清空list
 * @param  list [not null]
 */
#define etool_linkList_clear(list) \
do { \
	etool_memory_clear((list)->memory); \
	(list)->next = 0; \
} while(0)

/**
 * int etool_linkList_length(etool_linkList *list);
 * 获得list的有效长度
 * @param  list [description]
 */
#define etool_linkList_length(list) \
((list)->memory->length)

/**
 * int etool_linkList_empty(etool_linkList *list);
 * list是否为空
 * @param  list [description]
 */
#define etool_linkList_empty(list) \
((list)->next == 0)

/**
 * int etool_linkList_full(etool_linkList *list);
 * list是否已满
 * @param  list [description]
 */
#define etool_linkList_full(list) \
((list)->memory->length == (list)->memory->size)

/**
 * void* etool_linkList_find(etool_linkList *list, unsigned int index);
 * 查找list中的节点,O((n+1)/2)
 * @param  list  [description]
 * @param  index [description]
 * @param  value [description]
 * @param  type  [description]
 */
#define etool_linkList_find(list, index, value, type) \
do { \
	if (index >= 0 && index < (list)->memory->length) { \
		unsigned int _index = index; \
		struct _etool_linkNode *node = (list)->next; \
		while(_index > 0) { \
			_index--; \
			node = node->next; \
		} \
		value = *(type*)(node->data); \
	} \
} while(0)

/**
 * int etool_linkList_locate(etool_linkList *list, const void *value);
 * 定位list中的节点,O((n+1)/2)
 * @param  list  [description]
 * @param  value [description]
 * @param  index [description]
 * @param  type  [description]
 */
#define etool_linkList_locate(list, value, index, type) \
do { \
	struct _etool_linkNode *node = (list)->next; \
	for(index = 0; node != 0; index++) { \
		if (*(type*)(node->data) == value) { \
			break; \
		} \
		node = node->next; \
	} \
} while(0)

/**
 * int etool_linkList_insert(etool_linkList *list, unsigned int index, const void *value);
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  index [input data]
 * @param  value [input data]
 * @param  type [input data]
 */
#define etool_linkList_insert(list, index, value, type) \
do { \
	if (index >= 0 && index <= (list)->memory->length) { \
		unsigned int _index = index; \
		struct _etool_linkNode *newNode = (struct _etool_linkNode*)etool_memory_malloc((list)->memory); \
		if (newNode != 0) { \
			newNode->data = (unsigned char*)newNode + sizeof(struct _etool_linkNode); \
			*(type*)(newNode->data) = value; \
			struct _etool_linkNode *node = (struct _etool_linkNode*)(list); \
			while(_index > 0) { \
				_index--; \
				node = node->next; \
			} \
			newNode->next = node->next; \
			node->next = newNode; \
		} \
	} \
} while(0)

/**
 * int etool_linkList_erase(etool_linkList *list, unsigned int index, void *value);
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  index [output data]
 * @param  value [output data]
 * @param  type [output data]
 */
#define etool_linkList_erase(list, index, value, type) \
do { \
	if (index >= 0 && index < (list)->memory->length) { \
		unsigned int _index = index; \
		struct _etool_linkNode *node = (struct _etool_linkNode*)(list); \
		while(_index > 0) { \
			_index--; \
			node = node->next; \
		} \
		value = *(type*)(node->next->data); \
		etool_memory_free((list)->memory, node->next); \
		node->next = node->next->next; \
	} \
} while(0)

/**
 * int etool_linkList_copy(etool_linkList *srcList, etool_linkList *dstList);
 * 拷贝数据,O(n)
 * @param srclist [description]
 * @param dstlist [description]
 * @param type [description]
 */
#define etool_linkList_copy(srcList, dstList, type) \
do { \
	struct _etool_linkNode *srcNode = (struct _etool_linkNode*)(srcList)->next; \
	struct _etool_linkNode *dstNode = (struct _etool_linkNode*)(dstList); \
	etool_memory_clear((dstList)->memory); \
	struct _etool_linkNode *newNode = 0; \
	while (srcNode != 0) { \
		newNode = (struct _etool_linkNode*)etool_memory_malloc((dstList)->memory); \
		if (newNode != 0) { \
			newNode->data = (unsigned char*)newNode + sizeof(struct _etool_linkNode); \
			*(type*)(newNode->data) = *(type*)(srcNode->data); \
			dstNode->next = newNode; \
			dstNode = newNode; \
		} \
		srcNode = srcNode->next; \
	} \
	dstNode->next = 0; \
} while(0)

/**
 * etool_linkListIterator* etool_linkListIterator_init(etool_linkList *list)
 * 遍历迭代器
 * @param  list [description]
 * @param  block [description]
 * @param  element [description]
 * @param  type [description]
 */
#define etool_linkList_iterator(list, block, element, type) \
do { \
	type *element; \
	struct _etool_linkNode *node = (list)->next; \
	while (node != 0) { \
		element = (type*)(node->data); \
		block \
		node = node->next; \
	} \
} while(0)

#endif //ETOOL_TYPE_LINKLIST