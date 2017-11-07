/**
 * Copyright 2017, Geeks Road.  All rights reserved.
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
 * 创建list (动态存储表示)
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return          [实体]
 */
etool_circList* etool_circList_create(const unsigned int typeSize, const unsigned int size);

/**
 * 销毁list(动态存储表示)
 * @param  list [not null]
 * @return      [error code]
 */
void etool_circList_destroy(etool_circList *list);

/**
 * 获取一个list的总的大小
 * @param  typeSize [not null]
 * @param  size     [not null]
 * @return          [实体]
 */
int etool_circList_size(const unsigned int typeSize, const unsigned int size);

/**
 * 初始化一个list, 并且将一个数据源设入list(静态/动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @return          [实体]
 */
etool_circList* etool_circList_init(void *block, const unsigned int typeSize, const unsigned int size);

/**
 * 清空list
 * @param  list [not null]
 */
void etool_circList_clear(etool_circList *list);

/**
 * 获得list的有效长度
 * @param  list [description]
 * @return      [description]
 */
int etool_circList_length(etool_circList *list);

/**
 * list是否为空
 * @param  list [description]
 * @return      [bool code]
 */
int etool_circList_empty(etool_circList *list);

/**
 * list是否已满
 * @param  list [description]
 * @return      [bool code]
 */
int etool_circList_full(etool_circList *list);

/**
 * 查找list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  index [description]
 * @return      [description]
 */
void* etool_circList_find(etool_circList *list, unsigned int index);

/**
 * 定位list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  value [description]
 * @return      [description]
 */
int etool_circList_locate(etool_circList *list, void *value);

/*
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_circList_insert(etool_circList *list, unsigned int index, void *value);

/**
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_circList_erase(etool_circList *list, unsigned int index, void *value);

/**
 * 拷贝数据,O(n)
 * @param srclist [description]
 * @param dstlist [description]
 */
int etool_circList_copy(etool_circList *srcList, etool_circList *dstList);

#endif //ETOOL_TYPE_CIRCLIST