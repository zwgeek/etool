/**
 * Copyright 2017, Geeks Road.  All rights reserved.
 * 基于数组方式的线性表
 * 使用unsigned char(byte)来处理所有的数据类型
 */

#ifndef ETOOL_TYPE_SEQLIST
#define ETOOL_TYPE_SEQLIST

#include <stdlib.h>

#define ETOOL_MODE_CREATE	0
#define ETOOL_MODE_INIT		1
#define ETOOL_SEQLIST_EXTEND(list) \
unsigned char *_data = malloc(list->typeSize * list->size * 2); \
for (int n = 0; n < list->typeSize * list->size; n++) { \
	_data[n] = list->data[n]; \
} \
free(list->data); \
list->data = _data \

typedef struct _etool_seqList {
	unsigned char *data;
	unsigned int typeSize;
	unsigned int size;
	unsigned int length;
	unsigned int mode;
} etool_seqList;

/**
 * 创建list (动态存储表示)
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return      [实体]
 */
etool_seqList* etool_seqList_create(unsigned int typeSize, unsigned int size);

/**
 * 销毁list(动态存储表示)
 * @param  list [not null]
 * @return      [error code]
 */
void etool_seqList_destroy(etool_seqList *list);

/**
 * 创建一个符合要求的list需要的字节数
 * @param  typeSize [description]
 * @param  size     [description]
 * @return          [description]
 */
int etool_seqList_size(unsigned int typeSize, unsigned int size);

/**
 * 初始化一个list, 并且将一个数据源设入list(静态/动态存储表示),容器数据由开发者创建销毁
 * @param  block     [not null]
 * @param  typeSize [not null]
 * @param  size   [not null]
 * @return      [实体]
 */
etool_seqList* etool_seqList_init(void *block, unsigned int typeSize, unsigned int size);

/**
 * 清空list
 * @param  list [description]
 * @return      [description]
 */
void etool_seqList_clear(etool_seqList *list);

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
 * 查找list中的节点,O(1)
 * @param  list [description]
 * @return      [description]
 */
void* etool_seqList_find(etool_seqList *list, int index);

/**
 * 定位list中的节点,O((n+1)/2)
 * @param  list [description]
 * @return      [description]
 */
int etool_seqList_locate(etool_seqList *list, void *value);

/**
 * 插入节点,O(n/2)
 * @param  list [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_seqList_insert(etool_seqList *list, unsigned int index, void *value);

/**
 * 插入节点,插到最后一个O(1)
 * @param  list [description]
 * @param  value [input data]
 * @return      [description]
 */
int etool_seqList_insertEx(etool_seqList *list, void *value);

/**
 * 删除节点,O((n-1)/2)
 * @param  list [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_seqList_erase(etool_seqList *list, unsigned int index, void *value);

/**
 * 删除节点,不讲究顺序O(1)
 * @param  list [description]
 * @param  value [output data]
 * @return      [description]
 */
int etool_seqList_eraseEx(etool_seqList *list, unsigned int index, void *value);

#endif //ETOOL_TYPE_SEQLIST
