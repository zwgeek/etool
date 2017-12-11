/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 信号量 POSIX 无名
 */

#ifndef ETOOL_SEMAPHORE
#define ETOOL_SEMAPHORE

typedef struct _etool_semaphore etool_semaphore;

/**
 * 创建
 * @param  initNum   [not null]
 * @return           [实体]
 */
etool_semaphore* etool_semaphore_create(const int initNum);

/**
 * 装载
 * @param semaphore [not null]
 * @param  initNum   [not null]
 * @return
 */
int etool_semaphore_load(etool_semaphore *semaphore, const int initNum);

/**
 * 卸载
 * @param semaphore [not null]
 */
void etool_semaphore_unload(etool_semaphore *semaphore);

/**
 * 销毁
 * @param semaphore [not null]
 */
void etool_semaphore_destroy(etool_semaphore *semaphore);

/**
 * 阻塞
 * @param semaphore [not null]
 */
void etool_semaphore_pend(etool_semaphore *semaphore);

/**
 * 尝试阻塞
 * @param  semaphore [not null]
 * @param  timeOut   [ms,not null]
 * @return           [error code]
 */
int etool_semaphore_trypend(etool_semaphore *semaphore, const int timeOut);

/**
 * 通知
 * @param semaphore [not null]
 */
void etool_semaphore_post(etool_semaphore *semaphore);

#endif //ETOOL_SEMAPHORE
