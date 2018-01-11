extern "C" {
#include "../src/platform/System.h"
#include "../src/type/CircList.h"
#include "../src/type/CircQueue.h"
#include "../src/type/DblList.h"
#include "../src/type/LinkList.h"
#include "../src/type/LinkQueue.h"
#include "../src/type/LinkStack.h"
#include "../src/type/SeqList.h"
#include "../src/type/SeqStack.h"
}

int type_circList_test()
{
long start = etool_os_clock();
	etool_circList *list = 0;
	etool_circList_init(list, 10, int);
long start1 = etool_os_clock();
	for (unsigned int i = 0; i < 31; i++) {
		// printf("add %d\n", i);
		etool_circList_insert(list, i, i, int);
		//printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_circNode*)list->memory->freeAddr[i])->next);
	}
	etool_circList_clear(list);
	for (unsigned int i = 0; i < 99; i++) {
		// printf("add %d\n", i);
		// int a = i*2;
		etool_circList_insert(list, i, i, int);
		//printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[i], list->memory->length, ((struct _etool_circNode*)list->memory->freeAddr[i])->next);
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	unsigned int i = 0;
	etool_circList_erase(list, 5, i, int);
	// printf("add %d : %p\n", list->memory->length, list->memory->freeAddr[list->memory->length]);
	etool_circList_insert(list, 5, i, int);
	// printf("add %d, %p : %d  , %p\n", 5, list->memory->freeAddr[5], list->memory->length, ((struct _etool_circNode*)list->memory->freeAddr[5])->next);

	etool_circList_insert(list, 8, i, int);
	etool_circList_insert(list, 11, i, int);
	etool_circList_insert(list, 12, i, int);
	etool_circList_insert(list, 16, i, int);
	etool_circList_insert(list, 14, i, int);
	etool_circList_insert(list, 20, i, int);
	
	etool_circList_erase(list, 20, i, int);
	etool_circList_erase(list, 14, i, int);
	etool_circList_erase(list, 16, i, int);
	etool_circList_erase(list, 12, i, int);
	etool_circList_erase(list, 11, i, int);
	etool_circList_erase(list, 8, i, int);
	
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

	//printf("List 5 erase node : %d\n", i);
	int i2 = (int)(i + 2);
	unsigned int n;
	etool_circList_locate(list, i2, n, int);
	if (n == etool_circList_length(list)) {
		printf("List %d locate node\n", -1);
	} else {
		printf("List %d locate node\n", n);
	}
	printf("List length : %d\n", etool_circList_length(list));
	// printf("List size : %d, %d\n", list->memory->size, sizeof(int));
	etool_circList_find(list, 8, i2, int);
	printf("List 5 node : %d\n", i2);
	
	etool_circList_iterator(list, {
		printf("List node : %d\n", *data);
	}, data, int);
	

	etool_circList *dlist = 0;
	etool_circList_init(dlist, 10, int);
	etool_circList_copy(list, dlist, int);

	etool_circList_iterator(dlist, {
		printf("dList node : %d\n", *data);
	}, data, int);
	

	etool_circList_free(list);
	etool_circList_free(dlist);

long end = etool_os_clock();
printf("start : %ld, %ld, %ld\n", start, start1, (long)CLOCKS_PER_SEC);
printf("end : %ld, %ld\n",  end, end - start1 );
	return 0;
}

int type_circQueue_test()
{
long start = etool_os_clock();
	etool_circQueue *queue = 0;
	etool_circQueue_init(queue, 1000, long);
long start1 = etool_os_clock();
	// for (int i = 0; i < 11; i++) {
	// 	//printf("add %d\n", i);
	// 	if (etool_circQueue_enter(queue, &i) == -1) {
	// 		printf("-1");
	// 		return -1;
	// 	}
	// }
	// etool_circQueue_exit(queue, &i);
	// printf("exit %d \n", i);
	// etool_circQueue_clear(queue);
	for (long i = 0; i < 10000000; i++) {
		//printf("add %d\n", i);
		// int a = i*2;
		etool_circQueue_enter(queue, i, long);
		// if ( == -1) {
		// 	printf("-1");
		// 	return -1;
		// }
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	
	// etool_circQueue_head(queue, i, long);
	// printf("head %d \n", i);
	// etool_circQueue_exit(queue, i, long);
	// printf("exit %d \n", i);
	// etool_circQueue_exit(queue, i, long);
	// printf("exit %d\n", i);


	// etool_circQueue_peer_head(queue, i, long);
	// printf("peer_head %d \n", i);
	// etool_circQueue_peer_exit(queue, i, long);
	// printf("peer_exit %d \n", i);
	// etool_circQueue_exit(queue, i, long);
	// printf("exit %d\n", i);


	// etool_circQueue_enter(queue, i, long);
	// printf("enter %d\n", i);

	// etool_circQueue_peer_enter(queue, i, long);
	// printf("peer_enter %d\n", i);

	// // etool_circList_clear(queue);
	// // for (int i = 0; i < 31; i++) {
	// // 	printf("add %d\n", i);
	// // 	int a = i*2;
	// // 	if (etool_circList_insert(queue, i, &a) == -1) {
	// // 		printf("-1");
	// // 		return -1;
	// // 	}
	// // 	printf("add %d : %p , %p\n", i, queue->memory->freeAddr[i], ((struct _etool_circNode*)queue->memory->freeAddr[i])->next);
	// // }

	// printf("queue front : %d\n", queue->front);
	// printf("queue rear : %d\n", queue->rear);
	// printf("queue length : %d\n", etool_circQueue_length(queue));
	// printf("queue size : %d\n", queue->size);
	// etool_circQueue_iterator(queue, {
	// 	printf("queue node : %ld\n", *c);
	// }, c, long);
		
	// etool_circQueue_destroy(queue);
long end = etool_os_clock();
printf("start : %ld, %ld, %ld\n", start, start1, (long)CLOCKS_PER_SEC);
printf("end : %ld, %ld\n",  end, end - start1 );
	return 0;	
}

int type_dblList_test()
{
	etool_dblList *list = 0;
	etool_dblList_init(list, 10, int);
	for (unsigned int i = 0; i < 31; i++) {
		// printf("add %p\n", list->next);
		etool_dblList_insert(list, i, i, int);
		// printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_dblNode*)list->memory->freeAddr[i])->next);
	}
	etool_dblList_clear(list);
	for (unsigned int i = 0; i < 21; i++) {
		etool_dblList_insert(list, i, i, int);
		// printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[i], list->memory->length, ((struct _etool_dblNode*)list->memory->freeAddr[i])->next);
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	unsigned int i;
	etool_dblList_erase(list, -5, i, int);
	// printf("add %d : %p\n", list->memory->length, list->memory->freeAddr[list->memory->length]);
	etool_dblList_insert(list, 5, i, int);
	// printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[5], list->memory->length, ((struct _etool_dblNode*)list->memory->freeAddr[5])->next);

	etool_dblList_insert(list, 8, i, int);
	etool_dblList_insert(list, 11, i, int);
	etool_dblList_insert(list, 12, i, int);
	etool_dblList_insert(list, 16, i, int);
	etool_dblList_insert(list, 14, i, int);
	etool_dblList_insert(list, 20, i, int);

	etool_dblList_erase(list, 20, i, int);
	etool_dblList_erase(list, 14, i, int);
	etool_dblList_erase(list, 16, i, int);
	etool_dblList_erase(list, 12, i, int);
	etool_dblList_erase(list, 11, i, int);
	etool_dblList_erase(list, 8, i, int);

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
	int i2 = (int)(i + 1);
	unsigned int n = 0;
	etool_dblList_locate(list, i2, n, int);
	if (n == etool_dblList_length(list)) {
		printf("List %d locate node\n", n);
	} else {
		printf("List %d locate node\n", n);
	}
	etool_dblList_find(list, 8, i2, int);
	printf("List 8 node : %d\n", i2);

	printf("List length : %d\n", etool_dblList_length(list));
	printf("List size : %d\n", list->memory->size);
	
	etool_dblList_iterator(list, {
		printf("List node : %d\n", *data);
	}, data, int);

	etool_dblList *dlist = 0;
	etool_dblList_init(dlist, 10, int);

	etool_dblList_copy(list, dlist, int);

	
	etool_dblList_iterator(dlist, {
		printf("dList node : %d\n", *data);
	}, data, int);

	etool_dblList_free(list);
	etool_dblList_free(dlist);

	return 0;
}

int type_LinkList_test()
{
	etool_linkList *list = 0;
	etool_linkList_init(list, 10, int);
	for (unsigned int i = 0; i < 31; i++) {
		etool_linkList_insert(list, i, i, int);
		printf("add %d : %p , %p\n", i, list->next, ((struct _etool_linkNode*)list->memory->freeAddr[i])->next);
	}
	etool_linkList_clear(list);
	printf("List length : %d\n", etool_linkList_length(list));
	for (unsigned int i = 0; i < 21; i++) {
		etool_linkList_insert(list, i, i, int);
		printf("add %d, %p : %d  , %p\n", i, list->next, list->memory->length, ((struct _etool_linkNode*)list->memory->freeAddr[i])->next);
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	unsigned int i;
	etool_linkList_erase(list, 5, i, int);
	printf("add %d : %p\n", list->memory->length, list->memory->freeAddr[list->memory->length]);
	etool_linkList_insert(list, 5, i, int);
	printf("add %d, %p : %d  , %p\n", i, list->memory->freeAddr[5], list->memory->length, ((struct _etool_linkNode*)list->memory->freeAddr[5])->next);

	etool_linkList_insert(list, 8, i, int);
	etool_linkList_insert(list, 11, i, int);
	etool_linkList_insert(list, 12, i, int);
	etool_linkList_insert(list, 16, i, int);
	etool_linkList_insert(list, 14, i, int);
	etool_linkList_insert(list, 20, i, int);

	etool_linkList_erase(list, 20, i, int);
	etool_linkList_erase(list, 14, i, int);
	etool_linkList_erase(list, 16, i, int);
	etool_linkList_erase(list, 12, i, int);
	etool_linkList_erase(list, 11, i, int);
	etool_linkList_erase(list, 8, i, int);
	
	// etool_circList_clear(list);
	// for (int i = 0; i < 31; i++) {
	// 	printf("add %d\n", i);
	// 	int a = i*2;
	// 	if (etool_linkList_insert(list, i, &a, 1) == -1) {
	// 		printf("-1");
	// 		return -1;
	// 	}
	// 	printf("add %d : %p , %p\n", i, list->memory->freeAddr[i], ((struct _etool_linkNode*)list->memory->freeAddr[i])->next);
	// }

	printf("List 5 erase node : %d\n", i);
	int i2 = i + 1;
	unsigned int n = 0;
	etool_linkList_locate(list, i2, n, int);
	if (n == etool_linkList_length(list)) {
		printf("List %d locate node\n", n);
	} else {
		printf("List %d locate node\n", n);
	}
	printf("List length : %d\n", etool_linkList_length(list));
	printf("List size : %d\n", list->memory->size);
	// etool_linkList_find(list, 8, i, int);
	// printf("List 8 node : %d\n", i);

	etool_linkList_iterator(list, {
		printf("List node : %d\n", *data);
	}, data, int);

	// etool_linkList *dlist = 0;
	// etool_linkList_init(dlist, 10, int);

	// etool_linkList_copy(list, dlist, int);

	
	// etool_linkList_iterator(list, {
	// 	printf("dList node : %d\n", *data);
	// }, data, int);

	// etool_linkList_free(list);
	// etool_linkList_free(dlist);

	return 0;
}

int type_LinkQueue_test()
{
	unsigned int i= 0;
	etool_linkQueue *queue = 0;
	etool_linkQueue_init(queue);
	for (i = 0; i < 11; i++) {
		// printf("add %d\n", i);
		etool_linkQueue_enter(queue, i, int);
	}
	etool_linkQueue_exit(queue, i, int);
	printf("exit %d \n", i);
	// etool_linkQueue_clear(queue);
	for (unsigned int i = 0; i < 11; i++) {
		// printf("add %d\n", i);
		etool_linkQueue_enter(queue, i, int);
	}
	// printf("addr : %p, %p\n", list->memory->freeAddr, list);
	// for (int i = 0; i < 44; i++) {
	// 	printf("add %d : %p\n", i, list->memory->freeAddr[i]);
	// }
	
	etool_linkQueue_head(queue, i, int);
	printf("head %d \n", i);
	etool_linkQueue_exit(queue, i, int);
	printf("exit %d \n", i);
	etool_linkQueue_exit(queue, i, int);
	printf("exit %d\n", i);


	etool_linkQueue_peer_head(queue, i, int);
	printf("peer_head %d \n", i);
	etool_linkQueue_peer_exit(queue, i, int);
	printf("peer_exit %d \n", i);
	etool_linkQueue_exit(queue, i, int);
	printf("exit %d\n", i);


	etool_linkQueue_enter(queue, i, int);
	printf("enter %d\n", i);

	etool_linkQueue_peer_enter(queue, i, int);
	printf("peer_enter %d\n", i);

	printf("queue front : %p\n", queue->front);
	printf("queue rear : %p\n", queue->rear);
	printf("queue length : %d\n", etool_linkQueue_length(queue));
	
	etool_linkQueue_iterator(queue, {
		printf("queue node : %d\n", *data);
	}, data, int);
	etool_linkQueue_free(queue);
	return 0;	
}

int type_LinkStack_test()
{
	unsigned int i= 0;
	etool_linkStack *stack = 0;
	etool_linkStack_init(stack);
	for (i = 0; i < 11; i++) {
		 printf("add %d\n", i);
		 etool_linkStack_push(stack, i, int);
	}
	etool_linkStack_pop(stack, i, int);
	printf("pop %d \n", i);
	etool_linkStack_clear(stack);
	for (unsigned int i = 0; i < 11; i++) {
		// printf("add %d\n", i);
		etool_linkStack_push(stack, i, int);
	}

	etool_linkStack_pop(stack, i, int);
	printf("pop %d \n", i);
	etool_linkStack_pop(stack, i, int);
	printf("pop %d\n", i);

	etool_linkStack_push(stack, i, int);
	printf("enter %d\n", i);

	printf("stack top : %p\n", stack->top);
	printf("stack length : %d\n", etool_linkStack_length(stack));
	
	etool_linkStack_iterator(stack, {
		printf("stack node : %d\n", *data);
	}, data, int);
	etool_linkStack_free(stack);
	return 0;	
}

int type_SeqList_test()
{
	unsigned int i= 0;
	etool_seqList *list = 0;
	etool_seqList_init(list, 1, int);
	for (i = 0; i < 11; i++) {
		 printf("add %d\n", i);
		 //etool_seqList_insertEx(list, i, int);
		 etool_seqList_insert(list, i, i, int);
	}
	// etool_seqList_eraseEx(list, 0, i, int);
	// printf("erase 0 %d \n", i);
	// etool_seqList_clear(list);
	// for (unsigned int i = 0; i < 11; i++) {
	// 	// printf("add %d\n", i);
	// 	etool_seqList_insertEx(list, i, int);
	// }

	// unsigned int a, b;
	// etool_seqList_erase(list, 1, a, int);
	// printf("erase 1 %d \n", a);
	// etool_seqList_erase(list, 2, b, int);
	// printf("erase 2 %d\n", b);

	// etool_seqList_insert(list, 2, b, int);
	// printf("insert %d\n", b);

	// etool_seqList_insert(list, 1, a, int);
	// printf("insert %d\n", a);

	// printf("list size : %d\n", list->size);
	// printf("list length : %d\n", etool_seqList_length(list));
	// etool_seqList_locate(list, 0, a, int);
	// printf("list length index = %d : %d\n", 0, a);
	
	etool_seqList_iterator(list, {
		printf("list node : %d\n", *data);
	}, data, int);
	etool_seqList_free(list);
	return 0;	
}

int type_SeqStack_test()
{
	unsigned int i= 0;
	etool_seqStack *stack = 0;
	etool_seqStack_init(stack, 1, int);
	for (i = 0; i < 11; i++) {
		 printf("add %d\n", i);
		 etool_seqStack_push(stack, i, int);
		 //etool_seqStack_other_push(stack, i, int);
	}

	// etool_seqStack_other_pop(stack, i, int);
	// printf("pop %d \n", i);
	// etool_seqStack_clear(stack);
	// for (unsigned int i = 0; i < 11; i++) {
	// 	// printf("add %d\n", i);
	// 	etool_seqStack_other_push(stack, i, int);
	// }

	// etool_seqStack_other_pop(stack, i, int);
	// printf("pop %d \n", i);
	// etool_seqStack_other_pop(stack, i, int);
	// printf("pop %d\n", i);

	// etool_seqStack_other_push(stack, i, int);
	// printf("push %d\n", i);

	// printf("stack top : %d\n", stack->top);
	// printf("stack bottom : %d\n", stack->bottom);
	// printf("stack length : %d\n", etool_seqStack_other_length(stack));
	
	etool_seqStack_other_iterator(stack, {
	//etool_seqStack_iterator(stack, {
		printf("stack node : %d\n", *data);
	}, data, int);
	etool_seqStack_free(stack);
	return 0;	
}