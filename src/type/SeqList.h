/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 基于数组方式的线性表
 */

#ifndef ETOOL_TYPE_SEQLIST
#define ETOOL_TYPE_SEQLIST

#include <stdlib.h>

#define ETOOL_SEQLIST_EXTEND(list, type) \
unsigned int n; \
type *_data = (type*)malloc((list)->size << 1 * sizeof(type)); \
for (n = 0; n < (list)->size; n++) { \
	_data[n] = ((type*)((list)->data))[n]; \
} \
free((list)->data); \
(list)->data = (unsigned char*)_data; \
(list)->size = (list)->size << 1

typedef struct _etool_seqList {
	unsigned char *data;
	unsigned int size;
	unsigned int length;
} etool_seqList;


/**
 * 初始化一个list, 并且将一个数据源设入list(动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @param  volume [not null]
 * @param  type   [not null]
 */
#define etool_seqList_init(list, volume, type) \
do { \
	list = (etool_seqList*)malloc(sizeof(etool_seqList)); \
	if (list != 0) { \
		(list)->data = (unsigned char*)malloc(volume * sizeof(type)); \
		if ((list)->data != 0) { \
			(list)->size = volume; \
			(list)->length = 0; \
		} else { \
			free(list); \
			list = 0; \
		} \
	} \
} while(0)

/**
 * void etool_seqList_destroy(etool_seqList *list);
 * 销毁list(动态存储表示)
 * @param  list [not null]
 */
#define etool_seqList_free(list) \
do { \
	free((list)->data); \
	free(list); \
	list = 0; \
} while(0)

/**
 * void etool_seqList_clear(etool_seqList *list);
 * 清空list
 * @param  list [description]
 */
#define etool_seqList_clear(list) \
do { \
	(list)->length = 0; \
} while(0)

/**
 * int etool_seqList_length(etool_seqList *list);
 * 获得list的有效长度
 * @param  list [description]
 */
#define etool_seqList_length(list) \
((list)->length)

/**
 * int etool_seqList_empty(etool_seqList *list);
 * list是否为空
 * @param  list [description]
 */
#define etool_seqList_empty(list) \
((list)->length == 0)

/**
 * int etool_seqList_full(etool_seqList *list);
 * list是否已满
 * @param  list [description]
 */
#define etool_seqList_full(list) \
((list)->length == (list)->size)

/**
 * void* etool_seqList_find(etool_seqList *list, const unsigned int index);
 * 查找list中的节点,O(1)
 * @param  list [description]
 * @param  index [description]
 * @param  value [description]
 * @param  type [description]
 */
#define etool_seqList_find(list, index, value, type) \
do { \
	if (index >= 0 && index < (list)->length) { \
		value = ((type*)((list)->data))[index]; \
	} \
} while(0)

/**
 * int etool_seqList_locate(etool_seqList *list, const void *value);
 * 定位list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  value [description]
 * @param  index [description]
 * @param  type [description]
 */
#define etool_seqList_locate(list, value, index, type) \
do { \
	for (index = 0; index < (list)->length; index++) { \
		if (((type*)((list)->data))[index] == value) { \
			break; \
		} \
	} \
} while(0)

/**
 * int etool_seqList_insert(etool_seqList *list, const unsigned int index, const void *value);
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  index [description]
 * @param  value [input data]
 * @param  type [input data]
 */
#define etool_seqList_insert(list, index, value, type) \
do { \
	if (index >= 0 && index <= (list)->length) { \
		if ((list)->length == (list)->size) { \
			ETOOL_SEQLIST_EXTEND(list, type); \
		} \
		unsigned int _index; \
		for (_index = (list)->length - 1; _index >= index; _index--) { \
			((type*)((list)->data))[_index + 1] = ((type*)((list)->data))[_index]; \
		} \
		((type*)((list)->data))[index] = value; \
		(list)->length++; \
	} \
} while(0)

/**
 * int etool_seqList_insertEx(etool_seqList *list, const void *value);
 * 插入节点,插到最后一个O(1)
 * @param  list [description]
 * @param  value [input data]
 * @param  type [input data]
 */
#define etool_seqList_insertEx(list, value, type) \
do { \
	if ((list)->length == (list)->size) { \
		ETOOL_SEQLIST_EXTEND(list, type); \
	} \
	((type*)((list)->data))[(list)->length] = value; \
	(list)->length++; \
} while(0)

/**
 * int etool_seqList_erase(etool_seqList *list, const unsigned int index, void *value);
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  index [description]
 * @param  value [output data]
 * @param  type [output data]
 */
#define etool_seqList_erase(list, index, value, type) \
do { \
	if (index >= 0 && index < (list)->length) { \
		(list)->length--; \
		value = ((type*)((list)->data))[index]; \
		unsigned int _index; \
		for (_index = index; _index <= (list)->length; _index++) { \
			((type*)((list)->data))[_index] = ((type*)((list)->data))[_index + 1]; \
		} \
	} \
} while(0)

/**
 * int etool_seqList_eraseEx(etool_seqList *list, const unsigned int index, void *value);
 * 删除节点,用最后一个填充删除的位置,不讲究顺序O(1)
 * @param  list [description]
 * @param  index [description]
 * @param  value [output data]
 * @param  type [output data]
 */
#define etool_seqList_eraseEx(list, index, value, type) \
do { \
	if (index >= 0 && index < (list)->length) { \
		(list)->length--; \
		value = ((type*)((list)->data))[index]; \
		((type*)((list)->data))[index] = ((type*)((list)->data))[(list)->length]; \
	} \
} while(0)

/**
 * etool_seqListIterator* etool_seqListIterator_init(etool_seqList *list);
 * 遍历迭代器
 * @param  list [description]
 * @param  block [description]
 * @param  element [description]
 * @param  type [description]
 */
#define etool_seqList_iterator(list, block, element, type) \
do { \
	type *element; \
	unsigned int num; \
	for (num = 0; num < (list)->length; num++) { \
		element = (type*)((list)->data) + num; \
		block \
	} \
} while(0)

#endif //ETOOL_TYPE_SEQLIST
