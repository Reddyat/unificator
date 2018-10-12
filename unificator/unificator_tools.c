#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

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

void unificator_format_message(char * message, char * filename, 
    const UnificatorDynamicArray * duplicates, int processing_time)
{
    /* Message : <filename> : <duplicates> in <processing_time> microseconds.\n */
    size_t remaining_size = MESSAGE_SIZE_MAX;
    size_t position = 0;
    size_t writed_counter = 0;

    writed_counter = snprintf(&message[position], remaining_size, "%s : ", filename);
    position += writed_counter;
    remaining_size -= writed_counter;

    for ( size_t i = 0; i < duplicates->size; i++ )
    {
        writed_counter = snprintf(&message[position], remaining_size, "%"PRIu32" ", duplicates->data[i]);
        position += writed_counter;
        remaining_size -= writed_counter;
    }

    snprintf(&message[position], remaining_size, "in %d microseconds.\n", processing_time);
}