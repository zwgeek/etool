/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 条件变量
 */

#ifndef ETOOL_CONDITION
#define ETOOL_CONDITION

typedef struct _etool_condition etool_condition;

/**
 * 创建
 * @return           [实体]
 */
etool_condition* etool_condition_create();

/**
 * 装载
 * @param condition [not null]
 * @return
 */
int etool_condition_load(etool_condition *condition);

/**
 * 卸载
 * @param condition [not null]
 */
void etool_condition_unload(etool_condition *condition);

/**
 * 销毁
 * @param  condition [not null]
 */
void etool_condition_destroy(etool_condition *condition);

/**
 * 等待
 * @param condition [not null]
 * @param mutex     [not null]
 */
void etool_condition_wait(etool_condition *condition, etool_mutexEx *mutex);

/**
 * 尝试等待
 * @param  condition [not null]
 * @param  mutex     [not nul]
 * @param  timeOut   [ms,not nul]
 * @return           [error code]
 */
int etool_condition_trywait(etool_condition *condition, etool_mutexEx *mutex, const int timeOut);

/**
 * 通知
 * @param condition [not null]
 */
void etool_condition_signal(etool_condition *condition);

/**
 * 全部通知
 * @param condition [not null]
 */
void etool_condition_broadcast(etool_condition *condition);

#endif //ETOOL_CONDITION
