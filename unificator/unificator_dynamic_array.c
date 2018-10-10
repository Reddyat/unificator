#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "unificator_dynamic_array.h"

void unificator_dynamic_array_init(UnificatorDynamicArray * dynamic_array)
{
	if ( dynamic_array->data != NULL )
	{
		dynamic_array->data = malloc(UNIFICATOR_INITIAL_ARRAY_SIZE * sizeof(uint32_t));

		if ( dynamic_array->data != NULL)
		{
			dynamic_array->size = UNIFICATOR_INITIAL_ARRAY_SIZE * sizeof(uint32_t);
			dynamic_array->position = 0;
		}
		else
		{
			printf("Critical error: system seems to be out of memory.");
			exit(EXIT_FAILURE);
		}
	}
}

void unificator_dynamic_array_push(UnificatorDynamicArray * dynamic_array, const uint32_t new_value)
{
	if ( dynamic_array->data == NULL )
	{
		unificator_dynamic_array_init(dynamic_array);
	}

	/* Case of geting enough space in memory */
	if ( dynamic_array->position < dynamic_array->size )
	{
		dynamic_array->data[dynamic_array->position] = new_value;
		dynamic_array->position++;
	}
	else /* We need to resize the array. */
	{
		char * old_ptr = dynamic_array->data;

		/* We multiple by 2 the size each time we lack of space. */
		dynamic_array->data = realloc(dynamic_array->data, dynamic_array->size);

		/* Realloc succeed !!! */
		if ( dynamic_array->data != NULL )
		{
			dynamic_array->size *= 2;
			old_ptr = NULL;
		}
		else /* Realloc failed :( */
		{
			free(old_ptr);
			printf("Critical error: system seems to be out of memory.");
			exit(EXIT_FAILURE);
		}

		/* Now we can add the new element. */
		dynamic_array->data[dynamic_array->position] = new_value;
		dynamic_array->position++;
	}
}

void unificator_dynamic_array_free(UnificatorDynamicArray * dynamic_array)
{
	if ( dynamic_array->data != NULL )
	{
		free(dynamic_array->data);
		dynamic_array->data = NULL;
		dynamic_array->size = 0;
		dynamic_array->position = 0;
	}
}

void unificator_dynamic_array_print(UnificatorDynamicArray * dynamic_array)
{

}