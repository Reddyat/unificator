#include <assert.h>
#include <stdio.h>

#include "unificator_dynamic_array.h"

int main()
{
	printf("TEST OF UNIFICATOR_DYNAMIC_ARRAY : ");

	UnificatorDynamicArray test_da;

	/* Initialisation Test */
	unificator_dynamic_array_init(&test_da);
	// unificator_dynamic_array_print(&test_da);
	assert( test_da.data != NULL );
	assert( test_da.capacity == UNIFICATOR_INITIAL_ARRAY_CAPACITY );
	assert( test_da.size == 0 );

	unificator_dynamic_array_push(&test_da, 33);
	assert( test_da.data != NULL );
	assert( test_da.capacity == UNIFICATOR_INITIAL_ARRAY_CAPACITY );
	assert( test_da.size == 1 );
	assert ( test_da.data[0] == 33 );

	for ( int i = 0; i < 520; i++ )
	{
		unificator_dynamic_array_push(&test_da, 42);
	}

	assert( test_da.data != NULL );
	assert( test_da.capacity == UNIFICATOR_INITIAL_ARRAY_CAPACITY * 2 );
	assert( test_da.size == 521 );
	assert ( test_da.data[0] == 33 );
	assert ( test_da.data[520] == 42 );

	unificator_dynamic_array_clear(&test_da);
	assert ( test_da.size == 0 );

	unificator_dynamic_array_free(&test_da);
	assert( test_da.data == NULL );
	assert( test_da.capacity == 0 );
	assert( test_da.size == 0 );

	printf("OK\n");

	return 0;
}