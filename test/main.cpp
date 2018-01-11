#include <stdio.h>
#include "type.h"
#include "platform.h"

#include <vector>
using namespace std;

int test()
{
	int c = 0;
	c++;
	return 0;
}

int main(int argc, char *argv[])
{
	printf("hello, world\n");
	// type_circList_test();
	// type_circQueue_test();
	// type_dblList_test();
	// type_LinkList_test();
	// type_LinkQueue_test();
	// type_LinkStack_test();
	// type_SeqList_test();
	// type_SeqStack_test();
// 	vector <long> v;
// 	v.reserve(10000001);
// long start1 = etool_os_clock();
// 	for (long i = 0; i < 10000000; i++) {
// 		 v.push_back(i);
// 	}
// long end = etool_os_clock();
// printf("liststart : %ld, %ld\n", start1, (long)CLOCKS_PER_SEC);
// printf("listend : %ld, %ld\n",  end, end - start1 );


// long start11 = etool_os_clock();
// for (int i = 0; i < 5000000; i++) {
// test();
// }
// long end1 = etool_os_clock();
// printf("astart : %ld, %ld\n", start11, (long)CLOCKS_PER_SEC);
// printf("aend : %ld, %ld\n",  end1, end1 - start11 );

// printf("test %ld\n", 1 << 32);
// printf("longlong:%d, long:%d, int:%d\n", sizeof(long long), sizeof(long), sizeof(int));

// unsigned int a = 1;
// long start111 = etool_os_clock();
// for (int i = 0; i < 5000000; i++) {
// a <<= 2;
// }
// long end111 = etool_os_clock();
// printf("astart : %ld, %ld\n", start111, CLOCKS_PER_SEC);
// printf("aend : %ld, %ld\n",  end111, end111 - start111 );
// printf("%d\n", a);

// long start112 = etool_os_clock();
// for (int i = 0; i < 5000000; i++) {
// a *= 3;
// }
// long end112 = etool_os_clock();
// printf("astart : %ld, %ld\n", start112, CLOCKS_PER_SEC);
// printf("aend : %ld, %ld\n",  end112, end112 - start112 );
// printf("%d\n", a);



	type_thread_test();
	return 0;
}

