extern "C" {
#include "../src/type/CircList.h"
#include "../src/type/CircQueue.h"
#include "../src/type/DblList.h"
// #include "../src/type/LinkList.h"
#include "../src/type/LinkQueue.h"
// #include "../src/type/LinkStack.h"
}

int type_circList_test()
{
	etool_circList *list = etool_circList_create(sizeof(int), 10);
	for (int i = 0; i < 31; i++) {
		printf("add %d\n", i);
		if (etool_circList_insert(list, i, &i) == -1) {
			printf("-1");
			return -1;
		}
		printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_circNode*)list->memory->freeAddr[i])->next);
	}
	etool_circList_clear(list);
	for (int i = 0; i < 21; i++) {
		printf("add %d\n", i);
		int a = i*2;
		if (etool_circList_insert(list, i, &i) == -1) {
			printf("-1");
			return -1;
		}
		printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[i], list->memory->length, ((struct _etool_circNode*)list->memory->freeAddr[i])->next);
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	int i;
	etool_circList_erase(list, 5, &i);
	printf("add %d : %p\n", list->memory->length, list->memory->freeAddr[list->memory->length]);
	etool_circList_insert(list, 5, &i);
	printf("add %d, %p : %d  , %p\n", 5, list->memory->freeAddr[5], list->memory->length, ((struct _etool_circNode*)list->memory->freeAddr[5])->next);

	etool_circList_insert(list, 8, &i);
	etool_circList_insert(list, 11, &i);
	etool_circList_insert(list, 12, &i);
	etool_circList_insert(list, 16, &i);
	etool_circList_insert(list, 14, &i);
	etool_circList_insert(list, 20, &i);

	etool_circList_erase(list, 8, &i);
	etool_circList_erase(list, 11, &i);
	etool_circList_erase(list, 12, &i);
	etool_circList_erase(list, 16, &i);
	etool_circList_erase(list, 14, &i);
	etool_circList_erase(list, 20, &i);

	// int d = 0;
	// printf("ceshi 1 %c \n", i[d]);
	// printf("ceshi 2 %c :\n", i[d++]);
	// printf("ceshi 3 %d\n", d);
	// printf("ceshi 4 %c \n", i[d]);
	// printf("ceshi 5 %c :\n", i[++d]);
	// printf("ceshi 6 %d\n", d);

	// etool_circList_clear(list);
	// for (int i = 0; i < 31; i++) {
	// 	printf("add %d\n", i);
	// 	int a = i*2;
	// 	if (etool_circList_insert(list, i, &a) == -1) {
	// 		printf("-1");
	// 		return -1;
	// 	}
	// 	printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_circNode*)list->memory->freeAddr[i])->next);
	// }

	printf("List 5 erase node : %d\n", i);
	i+=2;
	int n = etool_circList_locate(list, &i);
	if (n == -1) {
		printf("List %d locate node\n", n);
	} else {
		printf("List %d locate node\n", n);
	}
	printf("List length : %d\n", etool_circList_length(list));
	printf("List size : %d\n", list->memory->size
		);
	printf("List 5 node : %d\n", *(int*)etool_circList_find(list, 8));
	etool_circListIterator *iterator = etool_circListIterator_init(list);
	do {
		printf("List node : %d\n", **(int**)(iterator));
	} while (etool_circListIterator_next(iterator));

	etool_circList *dlist = etool_circList_create(sizeof(int), 10);

	etool_circList_copy(list, dlist);

	etool_circListIterator *diterator = etool_circListIterator_init(dlist);
	do {
		printf("dList node : %d\n", **(int**)(diterator));
	} while (etool_circListIterator_next(diterator));

	etool_circList_destroy(list);

	return 0;
}

int type_circQueue_test()
{
	int i;
	etool_circQueue *queue = etool_circQueue_create(sizeof(int), 10);
	for (int i = 0; i < 11; i++) {
		printf("add %d\n", i);
		if (etool_circQueue_enter(queue, &i) == -1) {
			printf("-1");
			return -1;
		}
	}
	etool_circQueue_exit(queue, &i);
	printf("exit %d \n", i);
	// etool_circQueue_clear(queue);
	for (int i = 0; i < 11; i++) {
		printf("add %d\n", i);
		int a = i*2;
		if (etool_circQueue_enter(queue, &i) == -1) {
			printf("-1");
			return -1;
		}
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	
	etool_circQueue_head(queue, &i);
	printf("head %d \n", i);
	etool_circQueue_exit(queue, &i);
	printf("exit %d \n", i);
	etool_circQueue_exit(queue, &i);
	printf("exit %d\n", i);


	etool_circQueue_peer_head(queue, &i);
	printf("peer_head %d \n", i);
	etool_circQueue_peer_exit(queue, &i);
	printf("peer_exit %d \n", i);
	etool_circQueue_exit(queue, &i);
	printf("exit %d\n", i);


	etool_circQueue_enter(queue, &i);
	printf("enter %d\n", i);

	etool_circQueue_peer_enter(queue, &i);
	printf("peer_enter %d\n", i);

	// etool_circList_clear(queue);
	// for (int i = 0; i < 31; i++) {
	// 	printf("add %d\n", i);
	// 	int a = i*2;
	// 	if (etool_circList_insert(queue, i, &a) == -1) {
	// 		printf("-1");
	// 		return -1;
	// 	}
	// 	printf("add %d : %p , %p\n", i, queue->memory->freeAddr[i], ((struct _etool_circNode*)queue->memory->freeAddr[i])->next);
	// }

	printf("queue front : %d\n", queue->front);
	printf("queue rear : %d\n", queue->rear);
	printf("queue length : %d\n", etool_circQueue_length(queue));
	printf("queue size : %d\n", queue->size);
	etool_circQueueIterator *iterator = etool_circQueueIterator_init(queue);
	do {
		printf("queue node : %d\n", **(int**)(iterator));
	} while (etool_circQueueIterator_next(iterator));
	etool_circQueue_destroy(queue);
	return 0;	
}

int type_dblList_test()
{
	etool_dblList *list = etool_dblList_create(sizeof(int), 10);
	for (int i = 0; i < 31; i++) {
		printf("add %d\n", i);
		if (etool_dblList_insert(list, i, &i, 1) == -1) {
			printf("-1");
			return -1;
		}
		printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_dblNode*)list->memory->freeAddr[i])->next);
	}
	etool_dblList_clear(list);
	for (int i = 0; i < 21; i++) {
		printf("add %d\n", i);
		int a = i*2;
		if (etool_dblList_insert(list, i, &i, 1) == -1) {
			printf("-1");
			return -1;
		}
		printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[i], list->memory->length, ((struct _etool_dblNode*)list->memory->freeAddr[i])->next);
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	int i;
	etool_dblList_erase(list, 5, &i, 1);
	printf("add %d : %p\n", list->memory->length, list->memory->freeAddr[list->memory->length]);
	etool_dblList_insert(list, 5, &i, 1);
	printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[5], list->memory->length, ((struct _etool_dblNode*)list->memory->freeAddr[5])->next);

	etool_dblList_insert(list, 8, &i, 1);
	etool_dblList_insert(list, 11, &i, 1);
	etool_dblList_insert(list, 12, &i, 1);
	etool_dblList_insert(list, 16, &i, 1);
	etool_dblList_insert(list, 14, &i, 1);
	etool_dblList_insert(list, 20, &i, 1);

	etool_dblList_erase(list, 8, &i, 1);
	etool_dblList_erase(list, 11, &i, 1);
	etool_dblList_erase(list, 12, &i, 1);
	etool_dblList_erase(list, 16, &i, 1);
	etool_dblList_erase(list, 14, &i, 1);
	etool_dblList_erase(list, 20, &i, 1);

	// etool_circList_clear(list);
	// for (int i = 0; i < 31; i++) {
	// 	printf("add %d\n", i);
	// 	int a = i*2;
	// 	if (etool_dblList_insert(list, i, &a, 1) == -1) {
	// 		printf("-1");
	// 		return -1;
	// 	}
	// 	printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_dblNode*)list->memory->freeAddr[i])->next);
	// }

	printf("List 5 erase node : %d\n", i);
	i+=1;
	int n = etool_dblList_locate(list, &i);
	if (n == -1) {
		printf("List %d locate node\n", n);
	} else {
		printf("List %d locate node\n", n);
	}
	printf("List length : %d\n", etool_dblList_length(list));
	printf("List size : %d\n", list->memory->size);
	printf("List 5 node : %d\n", *(int*)etool_dblList_find(list, 8, 1));
	etool_dblListIterator *iterator = etool_dblListIterator_init(list);
	do {
		printf("List node : %d\n", **(int**)(iterator));
	} while (etool_dblListIterator_next(iterator));

	etool_dblList *dlist = etool_dblList_create(sizeof(int), 10);

	etool_dblList_copy(list, dlist);

	etool_dblListIterator *diterator = etool_dblListIterator_init(dlist);
	do {
		printf("dList node : %d\n", **(int**)(diterator));
	} while (etool_dblListIterator_next(diterator));	

	etool_dblList_destroy(list);
	etool_dblList_destroy(dlist);

	return 0;
}

// int type_LinkList_test()
// {
// 	etool_linkList *list = etool_linkList_create(sizeof(int), 10);
// 	for (int i = 0; i < 31; i++) {
// 		printf("add %d\n", i);
// 		if (etool_linkList_insert(list, i, &i) == -1) {
// 			printf("-1");
// 			return -1;
// 		}
// 		printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_linkNode*)list->memory->freeAddr[i])->next);
// 	}
// 	etool_linkList_clear(list);
// 	for (int i = 0; i < 21; i++) {
// 		printf("add %d\n", i);
// 		int a = i*2;
// 		if (etool_linkList_insert(list, i, &i) == -1) {
// 			printf("-1");
// 			return -1;
// 		}
// 		printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[i], list->memory->length, ((struct _etool_linkNode*)list->memory->freeAddr[i])->next);
// 	}
// 	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
// 	// for (int i = 0; i < 44; i++) {
// 	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
// 	// }
// 	int i;
// 	etool_linkList_erase(list, 5, &i);
// 	printf("add %d : %p\n", list->memory->length, list->memory->freeAddr[list->memory->length]);
// 	etool_linkList_insert(list, 5, &i);
// 	printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[5], list->memory->length, ((struct _etool_linkNode*)list->memory->freeAddr[5])->next);

// 	etool_linkList_insert(list, 8, &i);
// 	etool_linkList_insert(list, 11, &i);
// 	etool_linkList_insert(list, 12, &i);
// 	etool_linkList_insert(list, 16, &i);
// 	etool_linkList_insert(list, 14, &i);
// 	etool_linkList_insert(list, 20, &i);

// 	etool_linkList_erase(list, 8, &i);
// 	etool_linkList_erase(list, 11, &i);
// 	etool_linkList_erase(list, 12, &i);
// 	etool_linkList_erase(list, 16, &i);
// 	etool_linkList_erase(list, 14, &i);
// 	etool_linkList_erase(list, 20, &i);

// 	// etool_circList_clear(list);
// 	// for (int i = 0; i < 31; i++) {
// 	// 	printf("add %d\n", i);
// 	// 	int a = i*2;
// 	// 	if (etool_linkList_insert(list, i, &a, 1) == -1) {
// 	// 		printf("-1");
// 	// 		return -1;
// 	// 	}
// 	// 	printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_linkNode*)list->memory->freeAddr[i])->next);
// 	// }

// 	printf("List 5 erase node : %d\n", i);
// 	i+=1;
// 	int n = etool_linkList_locate(list, &i);
// 	if (n == -1) {
// 		printf("List %d locate node\n", n);
// 	} else {
// 		printf("List %d locate node\n", n);
// 	}
// 	printf("List length : %d\n", etool_linkList_length(list));
// 	printf("List size : %d\n", list->memory->size);
// 	printf("List 5 node : %d\n", *(int*)etool_linkList_find(list, 8));
// 	etool_linkListIterator *iterator = etool_linkListIterator_init(list);
// 	do {
// 		printf("List node : %d\n", **(int**)(iterator));
// 	} while (etool_linkListIterator_next(iterator));

// 	etool_linkList *dlist = etool_linkList_create(sizeof(int), 10);

// 	etool_linkList_copy(list, dlist);

// 	etool_linkListIterator *diterator = etool_linkListIterator_init(dlist);
// 	do {
// 		printf("dList node : %d\n", **(int**)(diterator));
// 	} while (etool_linkListIterator_next(diterator));	

// 	etool_linkList_destroy(list);
// 	etool_linkList_destroy(dlist);

// 	return 0;
// }

int type_LinkQueue_test()
{
	int i;
	etool_linkQueue *queue = etool_linkQueue_create(sizeof(int));
	for (int i = 0; i < 11; i++) {
		printf("add %d\n", i);
		if (etool_linkQueue_enter(queue, &i) == -1) {
			printf("-1");
			return -1;
		}
	}
	etool_linkQueue_exit(queue, &i);
	printf("exit %d \n", i);
	// etool_linkQueue_clear(queue);
	for (int i = 0; i < 11; i++) {
		printf("add %d\n", i);
		int a = i*2;
		if (etool_linkQueue_enter(queue, &i) == -1) {
			printf("-1");
			return -1;
		}
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	
	etool_linkQueue_head(queue, &i);
	printf("head %d \n", i);
	etool_linkQueue_exit(queue, &i);
	printf("exit %d \n", i);
	etool_linkQueue_exit(queue, &i);
	printf("exit %d\n", i);


	etool_linkQueue_peer_head(queue, &i);
	printf("peer_head %d \n", i);
	etool_linkQueue_peer_exit(queue, &i);
	printf("peer_exit %d \n", i);
	etool_linkQueue_exit(queue, &i);
	printf("exit %d\n", i);


	etool_linkQueue_enter(queue, &i);
	printf("enter %d\n", i);

	etool_linkQueue_peer_enter(queue, &i);
	printf("peer_enter %d\n", i);

	// etool_circList_clear(queue);
	// for (int i = 0; i < 31; i++) {
	// 	printf("add %d\n", i);
	// 	int a = i*2;
	// 	if (etool_circList_insert(queue, i, &a) == -1) {
	// 		printf("-1");
	// 		return -1;
	// 	}
	// 	printf("add %d : %p , %p\n", i, queue->memory->freeAddr[i], ((struct _etool_linkNode*)queue->memory->freeAddr[i])->next);
	// }

	printf("queue front : %p\n", queue->front);
	printf("queue rear : %p\n", queue->rear);
	printf("queue length : %d\n", etool_linkQueue_length(queue));
	etool_linkQueueIterator *iterator = etool_linkQueueIterator_init(queue);
	do {
		printf("queue node : %d\n", **(int**)(iterator));
	} while (etool_linkQueueIterator_next(iterator));
	etool_linkQueue_destroy(queue);
	return 0;	
}