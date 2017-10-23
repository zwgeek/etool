/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 基于数组方式的线性表
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_SEQLIST
#define ETOOL_TYPE_SEQLIST

#include <stdlib.h>

typedef struct {
	unsigned char *data;
	unsigned int typeSize;
	unsigned int size;
	unsigned int length;
} etool_seqList;

/**
 * 创建list (动态存储表示)
 * @param  list     [not null]
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return          [error code]
 */
int etool_seqList_create(etool_seqList *list, unsigned int typeSize, unsigned int size);

/**
 *  销毁list(动态存储表示)
 * @param  list [not null]
 * @return      [error code]
 */
void etool_seqList_destroy(etool_seqList *list);

/**
 * 初始化一个list, 并且将一个数据源设入list(静态/动态存储表示),容器数据由开发者创建销毁
 * @param  list     [not null]
 * @param  typeSize [not null]
 * @param  data     [not null]
 * @param  size   [not null]
 * @return          [error code]
 */
int etool_seqList_init(etool_seqList *list, unsigned int typeSize, void *data, unsigned int size);

/**
 * 清空list
 * @param  list [description]
 * @return      [description]
 */
int etool_seqList_clear(etool_seqList *list);

/**
 * 获得list的有效长度
 * @param  list [description]
 * @return      [description]
 */
int etool_seqList_length(etool_seqList *list);

/**
 * list是否为空
 * @param  list [description]
 * @return      [bool code]
 */
int etool_seqList_empty(etool_seqList *list);

/**
 * list是否已满
 * @param  list [description]
 * @return      [bool code]
 */
int etool_seqList_full(etool_seqList *list);

/**
 * 查找list中的节点
 * @param  list [description]
 * @return      [description]
 */
void* etool_seqList_find(etool_seqList *list, int index);

/**
 * 定位list中的节点
 * @param  list [description]
 * @return      [description]
 */
int etool_seqList_locate(etool_seqList *list, void *node);

/**
 * 插入节点
 * @param  list [description]
 * @param  node [input data]
 * @return      [description]
 */
int etool_seqList_insert(etool_seqList *list, unsigned int index, void *node);

/**
 * 删除节点
 * @param  list [description]
 * @param  node [output data]
 * @return      [description]
 */
int etool_seqList_erase(etool_seqList *list, unsigned int index, void *node);

/**
 * 扩容(只针对调用create函数使用)
 * @return      [description]
 */
int etool_seqList_extend();

#endif //ETOOL_TYPE_SEQLIST
