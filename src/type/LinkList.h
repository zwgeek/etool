/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 基于链表方式的线性表
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_LINKLIST
#define ETOOL_TYPE_SEQLIST

#include <stdlib.h>
#include "../pool/Memory.h"

typedef struct _etool_linkList {
	etool_memory *memory;
	struct _etool_node *next;
} etool_linkList;
struct _etool_node{
	unsigned char *data;
	struct _etool_node *next;
};

/**
 * 创建list (动态存储表示)
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return          [实体]
 */
etool_linkList* etool_linkList_create(unsigned int typeSize, unsigned int size);

/**
 *  销毁list(动态存储表示)
 * @param  list [not null]
 * @return      [error code]
 */
void etool_linkList_destroy(etool_linkList *list);

/**
 * 初始化一个list, 并且将一个数据源设入list(静态/动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @return          [实体]
 */
etool_linkList* etool_linkList_init(void *block);

/**
 * 清空list
 * @param  list [description]
 * @return      [description]
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
void* etool_linkList_find(etool_linkList *list, int index);

/**
 * 定位list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  value [description]
 * @return      [description]
 */
int etool_linkList_locate(etool_linkList *list, void *value);

/*
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_linkList_insert(etool_linkList *list, unsigned int index, void *value);

/*
 * 插入节点,插到最后一个O(1)
 * @param  list [description]
 * @param  value [input data]
 * @return      [description]
 */
// int etool_linkList_insertEx(etool_linkList *list, void *value);

/**
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_linkList_erase(etool_linkList *list, unsigned int index, void *value);

/**
 * 删除节点,不讲究顺序O(1)
 * @param  list [description]
 * @param  value [output data]
 * @return      [description]
 */
// int etool_linkList_eraseEx(etool_linkList *list, unsigned int index, void *value);

/**
 * 扩容(只针对调用create函数使用),O(n)
 * @return      [description]
 */
// int etool_linkList_extend(etool_linkList *list);

#endif //ETOOL_TYPE_LINKLIST