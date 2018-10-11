#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "unificator_dynamic_array.h"

void unificator_dynamic_array_init(UnificatorDynamicArray * dynamic_array)
{
	dynamic_array->data = malloc(UNIFICATOR_INITIAL_ARRAY_CAPACITY * sizeof(uint32_t));

	if ( dynamic_array->data != NULL)
	{
		dynamic_array->capacity = UNIFICATOR_INITIAL_ARRAY_CAPACITY;
		dynamic_array->size = 0;
	}
	else
	{
		printf("Critical error: system seems to be out of memory.");
		exit(EXIT_FAILURE);
	}
}

void unificator_dynamic_array_push(UnificatorDynamicArray * dynamic_array, const uint32_t new_value)
{
	if ( dynamic_array == NULL )
	{
		return;
	}

	if ( dynamic_array->data == NULL )
	{
		unificator_dynamic_array_init(dynamic_array);
	}

	/* Case of geting enough space in memory */
	if ( dynamic_array->size < dynamic_array->capacity )
	{
		dynamic_array->data[dynamic_array->size] = new_value;
		dynamic_array->size++;
	}
	else /* We need to resize the array. */
	{
		uint32_t * old_ptr = dynamic_array->data;

		/* We multiple by 2 the capacity each time we lack of space. */
		dynamic_array->data = realloc(dynamic_array->data, dynamic_array->capacity * sizeof(uint32_t) * 2);

		/* Realloc succeed !!! */
		if ( dynamic_array->data != NULL )
		{
			dynamic_array->capacity *= 2;
		}
		else /* Realloc failed :( */
		{
			free(old_ptr);
			printf("Critical error: system seems to be out of memory.");
			exit(EXIT_FAILURE);
		}

		/* Now we can add the new element. */
		dynamic_array->data[dynamic_array->size] = new_value;
		dynamic_array->size++;
	}
}

void unificator_dynamic_array_clear(UnificatorDynamicArray * dynamic_array)
{
	if ( dynamic_array == NULL )
	{
		return;
	}

	dynamic_array->size = 0;
}

void unificator_dynamic_array_free(UnificatorDynamicArray * dynamic_array)
{
	if ( dynamic_array == NULL )
	{
		return;
	}

	if ( dynamic_array->data != NULL )
	{
		free(dynamic_array->data);
		dynamic_array->data = NULL;
		dynamic_array->capacity = 0;
		dynamic_array->size = 0;
	}
}

void unificator_dynamic_array_print(UnificatorDynamicArray * dynamic_array)
{
	printf("Size     : %zu\n", dynamic_array->size);
	printf("Capacity : %zu\n", dynamic_array->capacity);
	printf("Data     :\n");

	for ( size_t i = 0; i < dynamic_array->size; i++ )
	{
		printf("%u ", dynamic_array->data[i]);
	}

	printf("\n");
}