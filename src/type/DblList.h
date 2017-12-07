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

typedef struct _etool_dblListIterator {
	unsigned char *data;
	struct _etool_dblNode *list;
	struct _etool_dblNode *next;
} etool_dblListIterator;

/**
 * 创建list (动态存储表示)
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return          [实体]
 */
etool_dblList* etool_dblList_create(const unsigned int typeSize, const unsigned int size);

/**
 * 销毁list(动态存储表示)
 * @param  list [not null]
 * @return      [error code]
 */
void etool_dblList_destroy(etool_dblList *list);

/**
 * 获取一个list的总的大小
 * @param  typeSize [not null]
 * @param  size     [not null]
 * @return          [实体]
 */
int etool_dblList_size(const unsigned int typeSize, const unsigned int size);

/**
 * 初始化一个list, 并且将一个数据源设入list(静态/动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @return          [实体]
 */
etool_dblList* etool_dblList_init(void *block, const unsigned int typeSize, const unsigned int size);

/**
 * 清空list
 * @param  list [not null]
 */
void etool_dblList_clear(etool_dblList *list);

/**
 * 获得list的有效长度
 * @param  list [description]
 * @return      [description]
 */
int etool_dblList_length(etool_dblList *list);

/**
 * list是否为空
 * @param  list [description]
 * @return      [bool code]
 */
int etool_dblList_empty(etool_dblList *list);

/**
 * list是否已满
 * @param  list [description]
 * @return      [bool code]
 */
int etool_dblList_full(etool_dblList *list);

/**
 * 查找list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  index [description]
 * @param  direction [-1:previous,1:next]
 * @return      [description]
 */
void* etool_dblList_find(etool_dblList *list, unsigned int index, int direction);

/**
 * 定位list中的节点,O((n+1)/2)
 * @param  list [description]
 * @param  value [description]
 * @return      [description]
 */
int etool_dblList_locate(etool_dblList *list, void *value);

/*
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  value [input data]
 * @param  direction [-1:previous,1:next]
 * @return      [description]
 */
int etool_dblList_insert(etool_dblList *list, unsigned int index, void *value, int direction);

/**
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  value [output data]
 * @param  direction [-1:previous,1:next]
 * @return      [description]
 */
int etool_dblList_erase(etool_dblList *list, unsigned int index, void *value, int direction);

/**
 * 拷贝数据,O(n)
 * @param srclist [description]
 * @param dstlist [description]
 */
int etool_dblList_copy(etool_dblList *srcList, etool_dblList *dstList);

/**
 * 创建迭代器
 * @param  list [description]
 * @return         [description]
 */
etool_dblListIterator* etool_dblListIterator_init(etool_dblList *list);

/**
 * 遍历迭代器
 * @param  iterator [description]
 * @return          [description]
 */
int etool_dblListIterator_next(etool_dblListIterator *iterator);

#endif //ETOOL_TYPE_CIRCLIST