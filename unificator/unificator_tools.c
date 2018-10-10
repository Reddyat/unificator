#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>

#include "unificator_tools.h"

int unificator_string_to_uint32(char * input_string, uint32_t * output_value)
{
    const int base = 10;
    char *endptr;
    uint32_t converted_value;

    errno = 0;
    converted_value = strtoul(input_string, &endptr, base);

    /* Check several error cases. */

    /* Too big number. */
    if ( (errno == ERANGE && converted_value == ULONG_MAX) )
    {
        return -1;
    }

    /* Invalid number. */
    if ( endptr == input_string && converted_value == 0 )
    {
    	return -1;
    }

    *output_value = converted_value;
    return 0;
}