/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 递归锁
 */

#ifndef ETOOL_RECURSIVEMUTEX
#define ETOOL_RECURSIVEMUTEX

typedef struct _etool_recursiveMutex etool_recursiveMutex;

/**
 * 创建
 * @return       [实体]
 */
etool_recursiveMutex* etool_recursiveMutex_create();

/**
 * 装载
 * @param mutex [not null]
 */
int etool_recursiveMutex_load(etool_recursiveMutex *mutex);

/**
 * 卸载
 * @param mutex [not null]
 * @return
 */
void etool_recursiveMutex_unload(etool_recursiveMutex *mutex);

/**
 * 销毁
 * @param mutex [not null]
 */
void etool_recursiveMutex_destroy(etool_recursiveMutex *mutex);

/**
 * 锁
 * @param mutex [not null]
 */
void etool_recursiveMutex_lock(etool_recursiveMutex *mutex);

/**
 * 尝试锁
 * @param  mutex [not null]
 * @return       [error code]
 */
int etool_recursiveMutex_trylock(etool_recursiveMutex *mutex);

/**
 * 解锁
 * @param mutex [not null]
 */
void etool_recursiveMutex_unlock(etool_recursiveMutex *mutex);

#endif //ETOOL_RECURSIVEMUTEX
