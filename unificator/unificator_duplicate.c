#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "unificator_dynamic_array.h"
#include "unificator_duplicate.h"
#include "unificator_sort.h"
#include "unificator_tools.h"

void unificator_find_duplicates(char * filepath,
    UnificatorDynamicArray * number_list, UnificatorDynamicArray * duplicate_list)
{
    /* Time to unificate */
    char * file_content = _read_file(filepath);

    if ( file_content != NULL )
    {
        char * token;
        token = strtok (file_content,"\n");
        while (token != NULL)
        { 
            /* Populate our dynamic_array. We almost multiple by 2 the space in RAM
               but will see afterwards if it's a problem. */
            uint32_t new_element;
            int res = unificator_string_to_uint32(token, &new_element);

            /* Convertion succeed. */
            if ( res == 0 )
            {
                unificator_dynamic_array_push(number_list, new_element);
            }
            else /* Convertion failed. */
            {
                fprintf(stderr, "Error: Convertion failed for the element %s in the file %s\n", token, filepath);
            }

            token = strtok(NULL, "\n");
        }

        /* Check if we have at least 2 elements. No needed to process otherwise. */
        if ( number_list->size >= 2 )
        {
            /* Sorting. */
            unificator_sort_array(number_list->data, number_list->size);

            /* Find duplicates. */
            /* We will check each element with the previous one to prevent buffer overflow. */
            /* That's why we begin the iterating to 1. */
            for ( size_t i = 1; i < number_list->size; i++ )
            {
                if ( number_list->data[i] == number_list->data[i-1] )
                {
                    /* Duplicate !!!!! */
                    unificator_dynamic_array_push(duplicate_list, number_list->data[i]);
                }
            }
        }

        free(file_content);
    }
    else
    {
        fprintf(stderr, "Error : unable to read the content of the file %s\n", filepath);
    }
}

char * _read_file(char * filepath)
{
    char * buffer = NULL;
    uint32_t string_size = 0;
    uint32_t read_size = 0;
    FILE * handler = fopen(filepath, "r");

    if (  handler )
    {
        /* Seek the last byte of the file */
        fseek(handler, 0, SEEK_END);
        /* Offset from the first to the last byte, or in other words, filesize */
        string_size = ftell(handler);
        /* go back to the start of the file */
        rewind(handler);

        /* Allocate a string that can hold it all */
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

        if ( buffer != NULL )
        {
            /* Read it all in one operation */
            read_size = fread(buffer, sizeof(char), string_size, handler);

            /* fread doesn't set it so put a \0 in the last position
            * and buffer is now officially a string */
            buffer[string_size] = '\0';

            if (string_size != read_size)
            {
                /* Something went wrong, throw away the memory and set
                * the buffer to NULL */
                free(buffer);
                buffer = NULL;
                fprintf(stderr, "Error: only %"PRIu32" read on %"PRIu32" bytes.\n", read_size, string_size);
            }
        }

        fclose(handler);
    }
    else
    {
        fprintf(stderr, "Error: unable to open the file %s.\n", filepath);
    }

    return buffer;
}