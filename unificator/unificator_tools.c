#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

#include "unificator_tools.h"

int unificator_string_to_uint16(char * input_string, uint16_t * output_value)
{
    char * end;
    errno = 0;
    intmax_t converted_value = strtoimax(input_string, &end, 10);

    if (errno == ERANGE || converted_value < 0 || converted_value > UINT16_MAX || end == input_string || *end != '\0')
    {
        return -1;
    }

    *output_value = (uint16_t) converted_value;
    
    return 0;
}

int unificator_string_to_uint32(char * input_string, uint32_t * output_value)
{
    char * end;
    errno = 0;
    intmax_t converted_value = strtoimax(input_string, &end, 10);

    if (errno == ERANGE || converted_value < 0 || converted_value > UINT32_MAX || end == input_string || *end != '\0')
    {
        return -1;
    }

    *output_value = (uint32_t) converted_value;
    
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