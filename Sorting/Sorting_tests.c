#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef int data_t;
const int MAX_DATA_VAL = 2147483647;

#include "quicksort.h"
#include "heap_sort.h"
#include "max_subarray.h"
#include "insert_sort.h"
#include "merge_sort.h"
#include "merge_insert_sort.h"

int* random_array (int min, int max, int len)
{
	int i;
	int* array = (int*)malloc (len * sizeof (int));

	srand (time (NULL));

	for (i = 0; i < len; i++)
	{
		array[i] = min + rand () % (max - min + 1);
	}

	return (array);
}


// Tests
void test_heap_sort(int* array, int len)
{
	int start = clock ();
	heap_sort (array, len);
	int finish = clock ();

	printf("test_heap_sort\n");
	int i;
	//for (i = 0; i < len; i++) printf("%d ", array[i]);
	printf("\nTIME: %d\n\n", finish - start);
}

void test_max_subarray(int* array, int len)
{
	int start = clock ();
	struct Subarray b = max_subarray (array, 0, len - 1);
	int finish = clock ();

	printf("test_max_subarray\n");
	printf("first: %d, last: %d, max summ: %d", b.first, b.last, b.summ);
	printf("\nTIME: %d\n\n", finish - start);
}

void test_insert_sort(int* array, int len)
{
	int start = clock ();
	insert_sort (array, len);
	int finish = clock ();

	printf("test_insert_sort\n");
	int i;
	//for (i = 0; i < len; i++) printf("%d ", array[i]);
	printf("\nTIME: %d\n\n", finish - start);
}

void test_merge_insert_sort(int* array, int len)
{
	int start = clock ();
	merge_insert_sort (array, 0, len - 1);
	int finish = clock ();

	printf("test_merge_insert_sort\n");
	int i;
	//for (i = 0; i < len; i++) printf("%d ", array[i]);
	printf("\nTIME: %d\n\n", finish - start);
}

void test_merge_sort(int* array, int len)
{
	int start = clock ();
	merge_sort (array, 0, len - 1);
	int finish = clock ();

	printf("test_merge_sort\n");
	int i;
	//for (i = 0; i < len; i++) printf("%d ", array[i]);
	printf("\nTIME: %d\n\n", finish - start);
}

void test_quicksort(int* array, int len)
{
	int start = clock ();
	quicksort (array, 0, len - 1);
	int finish = clock ();

	printf("test_quicksort\n");
	int i;
	//for (i = 0; i < len; i++) printf("%d ", array[i]);
	printf("\nTIME: %d\n\n", finish - start);
}



int main()
{
	int len;
	scanf("%d", &len);

	int* buf   = (int*)random_array(-1000, 1000, len);
	int* array = (int*)malloc(len * sizeof(int));
	memcpy(array, buf, len * sizeof(int));

	test_heap_sort(array, len);
	memcpy(array, buf, len * sizeof(int));

	test_max_subarray(array, len);
	memcpy(array, buf, len * sizeof(int));

	test_insert_sort(array, len);
	memcpy(array, buf, len * sizeof(int));

	test_merge_insert_sort(array, len);
	memcpy(array, buf, len * sizeof(int));

	test_merge_sort(array, len);
	memcpy(array, buf, len * sizeof(int));

	test_quicksort(array, len);
	memcpy(array, buf, len * sizeof(int));

	free(buf);
	free(array);

	return 0;
}
