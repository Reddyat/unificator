#include <stdint.h>
#include <stdlib.h>

#include "unificator_sort.h"

void unificator_sort_array(uint32_t * array, size_t array_size)
{
	qsort(array, array_size, sizeof(uint32_t), &unificator_compare_uint32_t);
}

int unificator_compare_uint32_t(const void * left_integer, const void * rigth_integer)
{
	if ( *((uint32_t *) left_integer) < *((uint32_t *) rigth_integer) )
	{
		return -1;
	}
	else if ( *((uint32_t *) left_integer) > *((uint32_t *) rigth_integer) )
	{
		return 1;
	}
	else /* Equal */
	{
		return 0;
	}
}