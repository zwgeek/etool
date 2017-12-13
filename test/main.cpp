#include <stdio.h>
extern "C" {
#include "../src/type/CircList.h"
}

int type_test()
{
	etool_circList *list = etool_circList_create(sizeof(int), 10);
	for (int i = 0; i < 20; i++) {
		printf("add %d\n", i);
		if (etool_circList_insert(list, i, &i) == -1) {
			printf("-1");
			return -1;
		}
	}
	int i;
	etool_circList_erase(list, 5, &i);
	printf("List 5 erase node : %d\n", i);
	i++;
	int n = etool_circList_locate(list, &i);
	if (i == -1) {
		printf("List %d locate node\n", n);
	} else {
		printf("List %d locate node\n", n);
	}
	printf("List length : %d\n", etool_circList_length(list));
	printf("List 5 node : %d\n", *(int*)etool_circList_find(list, 8));
	etool_circListIterator *iterator = etool_circListIterator_init(list);
	do {
		printf("List node : %d\n", **(int**)(iterator));
	} while (etool_circListIterator_next(iterator));
	return 0;
}

int main(int argc, char *argv[])
{
	printf("hello, world\n");
	type_test();
	return 0;
}

