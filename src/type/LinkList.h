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

typedef struct _etool_linkListIterator {
	unsigned char *data;
	struct _etool_linkNode *next;
} etool_linkListIterator;


/**
 * 初始化一个list, 并且将一个数据源设入list(动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @return          [实体]
 */
etool_linkList* etool_linkList_init(list, volume, type) \
do { \
		list = malloc(sizeof(etool_linkList));
		if (list != 0) {
			list->memory = etool_memory_create(sizeof(struct _etool_linkNode) + typeSize, size);
			if (list->memory != 0) {
				list->next = 0;
			} else {
				free(list);
				list = 0;
			}
		}
} while(0)


/**
 * 销毁list(动态存储表示)
 * @param  list [not null]
 * @return      [error code]
 */
void etool_linkList_free(etool_linkList *list);

/**
 * 清空list
 * @param  list [not null]
 */
void etool_linkList_clear(etool_linkList *list);

/**
 * 获得list的有效长度
 * @param  list [description]
 * @return      [description]
 */
int etool_linkList_length(etool_linkList *list);

/**
 * list是否为空
 * @param  list [description]
 * @return      [bool code]
 */
int etool_linkList_empty(etool_linkList *list);

/**
 * list是否已满
 * @param  list [description]
 * @return      [bool code]
 */
int etool_linkList_full(etool_linkList *list);

/**
 * 查找list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  index [description]
 * @return      [description]
 */
void* etool_linkList_find(etool_linkList *list, unsigned int index);

/**
 * 定位list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  value [description]
 * @return      [description]
 */
int etool_linkList_locate(etool_linkList *list, const void *value);

/*
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_linkList_insert(etool_linkList *list, unsigned int index, const void *value);

/**
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_linkList_erase(etool_linkList *list, unsigned int index, void *value);

/**
 * 拷贝数据,O(n)
 * @param srclist [description]
 * @param dstlist [description]
 */
int etool_linkList_copy(etool_linkList *srcList, etool_linkList *dstList);

/**
 * 创建迭代器
 * @param  list [description]
 * @return         [description]
 */
etool_linkListIterator* etool_linkListIterator_init(etool_linkList *list);

/**
 * 遍历迭代器
 * @param  iterator [description]
 * @return          [description]
 */
int etool_linkListIterator_next(etool_linkListIterator *iterator);

#endif //ETOOL_TYPE_LINKLIST