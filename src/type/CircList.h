/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于单循环链表方式的线性表
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_CIRCLIST
#define ETOOL_TYPE_CIRCLIST

#include <stdlib.h>
#include "../pool/Memory.h"

typedef struct _etool_circList {
	etool_memory *memory;
	struct _etool_circNode *next;
} etool_circList;

struct _etool_circNode {
	unsigned char *data;
	struct _etool_circNode *next;
};

/**
 * 初始化一个list, 并且将一个数据源设入list(动态存储表示),容器数据由开发者创建销毁
 * @param  list     [not null]
 * @param  volume   [not null]
 * @param  type     [not null]
 */
#define etool_circList_init(list, volume, type) \
do { \
	list = (etool_circList*)malloc(sizeof(etool_circList)); \
	if (list != 0) { \
		(list)->memory = etool_memory_create(sizeof(struct _etool_circNode) + sizeof(type), volume); \
		if ((list)->memory != 0) { \
			(list)->next = (struct _etool_circNode*)(list); \
		} else { \
			free(list); \
			list = 0; \
		} \
	} \
} while(0)

/**
 * void etool_circList_free(etool_circList *list);
 * 销毁list(动态存储表示)
 * @param  list [not null]
 */
#define etool_circList_free(list) \
do { \
	etool_memory_destroy((list)->memory); \
	free(list); \
	list = 0; \
} while(0)

/**
 * void etool_circList_clear(etool_circList *list);
 * 清空list
 * @param  list [not null]
 */
#define etool_circList_clear(list) \
do { \
	etool_memory_clear((list)->memory); \
	(list)->next = (struct _etool_circNode*)(list); \
} while(0)

/**
 * int etool_circList_length(etool_circList *list);
 * 获得list的有效长度
 * @param  list [description]
 */
#define etool_circList_length(list) \
(list)->memory->length

/**
 * int etool_circList_empty(etool_circList *list);
 * list是否为空
 * @param  list [description]
 */
#define etool_circList_empty(list) \
((list)->next == (struct _etool_circNode*)(list))

/**
 * int etool_circList_full(etool_circList *list);
 * list是否已满
 * @param  list [description]
 */
#define etool_circList_full(list) \
((list)->memory->length == (list)->memory->size)

/**
 * void* etool_circList_find(etool_circList *list, unsigned int index);
 * 查找list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  index [description]
 * @param  value [description]
 * @param  type [description]
 */
#define etool_circList_find(list, index, value, type) \
do { \
	if (index >= 0) { \
		unsigned int _index = index; \
		struct _etool_circNode *node = (list)->next; \
		while (_index > 0) { \
			_index--; \
			node = node->next; \
		} \
		value = *(type*)(node->data); \
	} \
} while(0)

/**
 * int etool_circList_locate(etool_circList *list, const void *value);
 * 定位list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  value [description]
 * @param  index [description]
 * @param  type [description]
 */
#define etool_circList_locate(list, value, index, type) \
do { \
	struct _etool_circNode *node = (list)->next; \
	for (index = 0; node != (struct _etool_circNode*)(list); index++) { \
		if (*(type*)(node->data) == value) { \
			break; \
		} \
		node = node->next; \
	} \
} while(0)

/**
 * int etool_circList_insert(etool_circList *list, unsigned int index, const void *value);
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  index [input data]
 * @param  value [input data]
 * @param  type [input data]
 */
#define etool_circList_insert(list, index, value, type) \
do { \
	if (index >= 0) { \
		unsigned int _index = index; \
		struct _etool_circNode *newNode = (struct _etool_circNode*)etool_memory_malloc((list)->memory); \
		if (newNode != 0) { \
			newNode->data = (unsigned char*)newNode + sizeof(struct _etool_circNode); \
			*(type*)(newNode->data) = value; \
			struct _etool_circNode *node = (struct _etool_circNode*)(list); \
			while (_index > 0) { \
				_index--; \
				node = node->next; \
			} \
			newNode->next = node->next; \
			node->next = newNode; \
		} \
	} \
} while(0)

/**
 * int etool_circList_erase(etool_circList *list, unsigned int index, void *value);
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  index [output data]
 * @param  value [output data]
 * @param  type [output data]
 */
#define etool_circList_erase(list, index, value, type) \
do { \
	if (index >= 0) { \
		unsigned int _index = index; \
		struct _etool_circNode *node = (struct _etool_circNode*)(list); \
		while(_index > 0) { \
			_index--; \
			node = node->next; \
		} \
		struct _etool_circNode *_node = node->next; \
		node->next = _node->next; \
		value = *(type*)(_node->data); \
		etool_memory_free((list)->memory, _node); \
	} \
} while(0)

/**
 * int etool_circList_copy(etool_circList *srcList, etool_circList *dstList);
 * 拷贝数据,O(n)
 * @param srcList [description]
 * @param dstList [description]
 * @param type [description]
 */
#define etool_circList_copy(srcList, dstList, type) \
do { \
	struct _etool_circNode *srcNode = (struct _etool_circNode*)(srcList)->next; \
	struct _etool_circNode *dstNode = (struct _etool_circNode*)(dstList); \
	etool_memory_clear((dstList)->memory); \
	struct _etool_circNode *newNode = 0; \
	while (srcNode != (struct _etool_circNode*)(srcList)) { \
		newNode = (struct _etool_circNode*)etool_memory_malloc((dstList)->memory); \
		if (newNode != 0) { \
			newNode->data = (unsigned char*)newNode + sizeof(struct _etool_circNode); \
			*(type*)(newNode->data) = *(type*)(srcNode->data); \
			dstNode->next = newNode; \
			dstNode = newNode; \
		} \
		srcNode = srcNode->next; \
	} \
	dstNode->next = (struct _etool_circNode*)(dstList); \
} while(0)

/**
 * etool_circListIterator* etool_circListIterator_init(etool_circList *list);
 * 遍历迭代器
 * @param  list [description]
 * @param  block [description]
 * @param  element [description]
 * @param  type [description]
 */
#define etool_circList_iterator(list, block, element, type) \
do { \
	type *element; \
	struct _etool_circNode *node = (list)->next; \
	while (node != (struct _etool_circNode*)(list)) { \
		element = (type*)(node->data); \
		block \
		node = node->next; \
	} \
} while(0)

#endif //ETOOL_TYPE_CIRCLIST