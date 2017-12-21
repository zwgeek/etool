#include <stdio.h>
#include "type.h"

#include <vector>
using namespace std;

int test()
{
	// int c = 0;
	// c++;
	return 0;
}

int main(int argc, char *argv[])
{
	printf("hello, world\n");
	// type_circList_test();
	type_circQueue_test();
	// type_dblList_test();
	// type_LinkList_test();
	// type_LinkQueue_test();
	vector <long> v;
	v.reserve(5000000);
long start1 = etool_os_clock();
	for (long i = 0; i < 5000000; i++) {
		 v.push_back(i);
	}
long end = etool_os_clock();
printf("liststart : %ld, %ld\n", start1, CLOCKS_PER_SEC);
printf("listend : %ld, %ld\n",  end, end - start1 );


long start11 = etool_os_clock();
for (int i = 0; i < 5000000; i++) {
test();
}
long end1 = etool_os_clock();
printf("astart : %ld, %ld\n", start11, CLOCKS_PER_SEC);
printf("aend : %ld, %ld\n",  end1, end1 - start11 ); 

	return 0;
}

