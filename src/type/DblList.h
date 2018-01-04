/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于双循环链表方式的线性表
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_DBLLIST
#define ETOOL_TYPE_DBLLIST

#include <stdlib.h>
#include "../pool/Memory.h"

typedef struct _etool_dblList {
	etool_memory *memory;
	struct _etool_dblNode *previous, *next;
} etool_dblList;

struct _etool_dblNode {
	unsigned char *data;
	struct _etool_dblNode *previous, *next;
};


/**
 * etool_dblList* etool_dblList_init(void *block, const unsigned int typeSize, const unsigned int size);
 * 初始化一个list, 并且将一个数据源设入list(动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 */
#define etool_dblList_init(list, volume, type) \
do { \
	list = (etool_dblList*)malloc(sizeof(etool_dblList)); \
	if (list != 0) { \
		(list)->memory = etool_memory_create(sizeof(struct _etool_dblNode) + sizeof(type), volume); \
		if ((list)->memory != 0) { \
			(list)->previous = (list)->next = (struct _etool_dblNode*)(list); \
		} else { \
			free(list); \
			list = 0; \
		} \
	} \
} while(0)

/**
 * void etool_dblList_destroy(etool_dblList *list);
 * 销毁list(动态存储表示)
 * @param  list [not null]
 */
#define etool_dblList_free(list) \
do { \
	etool_memory_destroy((list)->memory); \
	free(list); \
	list = 0; \
} while(0)

/**
 * void etool_dblList_clear(etool_dblList *list);
 * 清空list
 * @param  list [not null]
 */
#define etool_dblList_clear(list) \
do { \
	etool_memory_clear((list)->memory); \
	(list)->previous = (list)->next = (struct _etool_dblNode*)(list); \
} while(0)

/**
 * int etool_dblList_length(etool_dblList *list);
 * 获得list的有效长度
 * @param  list [description]
 */
#define etool_dblList_length(list) \
((list)->memory->length)

/**
 * int etool_dblList_empty(etool_dblList *list);
 * list是否为空
 * @param  list [description]
 */
#define etool_dblList_empty(list) \
((list)->next == (struct _etool_dblNode*)(list))

/**
 * int etool_dblList_full(etool_dblList *list);
 * list是否已满
 * @param  list [description]
 */
#define etool_dblList_full(list) \
((list)->memory->length == (list)->memory->size)

/**
 * void* etool_dblList_find(etool_dblList *list, unsigned int index, int direction);
 * 查找list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  index [-X:previous,X:next]
 * @param  value [description]
 * @param  type [description]
 */
#define etool_dblList_find(list, index, value, type) \
do { \
	int _index = index; \
	if (_index >= 0) { \
		struct _etool_dblNode *node = (list)->next; \
		while (_index > 0) { \
			_index--; \
			node = node->next; \
		} \
		value = *(type*)(node->data); \
	} else { \
		struct _etool_dblNode *node = (list)->previous; \
		do { \
			_index++; \
			node = node->previous; \
		} while(_index < 0); \
		value = *(type*)(node->data); \
	} \
} while(0)

/**
 * int etool_dblList_locate(etool_dblList *list, const void *value);
 * 定位list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  value [description]
 * @param  index [description]
 * @param  type [description]
 */
#define etool_dblList_locate(list, value, index, type) \
do { \
	struct _etool_dblNode *node = (list)->next; \
	for(index = 0; node != (struct _etool_dblNode*)(list); index++) { \
		if (*(type*)(node->data) == value) { \
			break; \
		} \
		node = node->next; \
	} \
} while(0)

/**
 * int etool_dblList_insert(etool_dblList *list, unsigned int index, const void *value, int direction);
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  index [-1:previous,1:next]
 * @param  value [description]
 * @param  type [description]
 */
#define etool_dblList_insert(list, index, value, type) \
do { \
	struct _etool_dblNode *newNode = (struct _etool_dblNode*)etool_memory_malloc((list)->memory); \
	if (newNode != 0) { \
		int _index = index; \
		newNode->data = (unsigned char*)newNode + sizeof(struct _etool_dblNode); \
		*(type*)(newNode->data) = value; \
		if (_index >= 0) { \
			struct _etool_dblNode *node = (list)->next; \
			while (_index > 0) { \
				_index--; \
				node = node->next; \
			} \
			newNode->previous = node->previous; \
			newNode->next = node; \
			node->previous = newNode; \
			newNode->previous->next = newNode; \
		} else { \
			struct _etool_dblNode *node = (list)->previous; \
			do { \
				_index++; \
				node = node->previous; \
			} while(_index < 0); \
			newNode->next = node->next; \
			newNode->previous = node; \
			node->next = newNode; \
			newNode->next->previous = newNode; \
		} \
	} \
} while(0)

/**
 * int etool_dblList_erase(etool_dblList *list, unsigned int index, void *value, int direction);
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  index [-1:previous,1:next]
 * @param  value [output data]
 * @param  type [output data]
 */
#define etool_dblList_erase(list, index, value, type) \
do { \
	int _index = index; \
	if (_index >= 0) { \
		struct _etool_dblNode *node = (list)->next; \
		while(_index > 0) { \
			_index--; \
			node = node->next; \
		} \
		node->previous->next = node->next; \
		node->next->previous = node->previous; \
		value = *(type*)(node->data); \
		etool_memory_free((list)->memory, node); \
	} else { \
		struct _etool_dblNode *node = (list)->previous; \
		do { \
			_index++; \
			node = node->previous; \
		} while(_index < 0); \
		node->previous->next = node->next; \
		node->next->previous = node->previous; \
		value = *(type*)(node->data); \
		etool_memory_free((list)->memory, node); \
	} \
} while(0)

/**
 * int etool_dblList_copy(etool_dblList *srcList, etool_dblList *dstList);
 * 拷贝数据,O(n)
 * @param srclist [description]
 * @param dstlist [description]
 * @param type [description]
 */
#define etool_dblList_copy(srcList, dstList, type) \
do { \
	struct _etool_dblNode *srcNode = (struct _etool_dblNode*)(srcList)->next; \
	struct _etool_dblNode *dstNode = (struct _etool_dblNode*)(dstList); \
	etool_memory_clear((dstList)->memory); \
	struct _etool_dblNode *newNode = 0; \
	while (srcNode != (struct _etool_dblNode*)(srcList)) { \
		newNode = (struct _etool_dblNode*)etool_memory_malloc((dstList)->memory); \
		if (newNode != 0) { \
			newNode->data = (unsigned char*)newNode + sizeof(struct _etool_dblNode); \
			*(type*)(newNode->data) = *(type*)(srcNode->data); \
			newNode->previous = dstNode; \
			dstNode->next = newNode; \
			dstNode = newNode; \
		} \
		srcNode = srcNode->next; \
	} \
	(dstList)->previous = dstNode; \
	dstNode->next = (struct _etool_dblNode*)(dstList); \
} while(0)

/**
 * etool_dblListIterator* etool_dblListIterator_init(etool_dblList *list);
 * 遍历迭代器
 * @param  list [description]
 * @param  block [description]
 * @param  element [description]
 * @param  type [description]
 */
#define etool_dblList_iterator(list, block, element, type) \
do { \
	type *element; \
	struct _etool_dblNode *node = (list)->next; \
	while (node != (struct _etool_dblNode*)(list)) { \
		element = (type*)(node->data); \
		block \
		node = node->next; \
	} \
} while(0)

#endif //ETOOL_TYPE_CIRCLIST