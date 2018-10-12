#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "unificator_sort.h"
#include "unificator_dynamic_array.h"

int main()
{
	printf("TEST OF UNIFICATOR_DYNAMIC_ARRAY : ");

	UnificatorDynamicArray test_da;
	unificator_dynamic_array_init(&test_da);
	unificator_dynamic_array_push(&test_da, 3);
	unificator_dynamic_array_push(&test_da, 1);
	unificator_dynamic_array_push(&test_da, 10);
	unificator_dynamic_array_push(&test_da, 5);
	unificator_dynamic_array_push(&test_da, 52);
	unificator_dynamic_array_push(&test_da, 0);
	unificator_dynamic_array_push(&test_da, 6);
	unificator_dynamic_array_push(&test_da, 2);

	unificator_sort_array(test_da.data, test_da.size);

	assert(test_da.data[0] == 0);
	assert(test_da.data[7] == 52);

	unificator_dynamic_array_free(&test_da);

	printf("OK\n");

	return 0;
}