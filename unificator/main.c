#include <stdio.h> 
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "unificator_tools.h"
#include "unificator_dynamic_array.h"
#include "unificator_sort.h"
#include "unificator_timer.h"

char* read_file(char * filename)
{
   char * buffer = NULL;
   int string_size = 0;
   int read_size = 0;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       /* Seek the last byte of the file */
       fseek(handler, 0, SEEK_END);
       /* Offset from the first to the last byte, or in other words, filesize */
       string_size = ftell(handler);
       /* go back to the start of the file */
       rewind(handler);

       /* Allocate a string that can hold it all */
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

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
       }

       fclose(handler);
    }

    return buffer;
}

int main()
{
	//TODO : Take the directory where to read the file as argument
	const char * output_directory = "/home/reddyat/workspace/unificator/working/";

    struct dirent * directory_entry;
  
    DIR * directory_pointer = opendir(output_directory);
  
    if (directory_pointer == NULL)
    { 
        printf("Could not open working directory : %s", output_directory); 
        return 0; 
    }

    /* We iterate on all files in the directory output_directory. */
    while ( (directory_entry = readdir(directory_pointer)) != NULL )
    {
    	/* We don't process hidden files and the current directory file "." */
    	if ( strncmp(directory_entry->d_name, ".", 1) != 0 )
    	{
            /* Begining of the process so we start the timer. */
            unificator_timer_start();

    		char full_filename[256];
    		strcpy(full_filename, output_directory);
    		strcat(full_filename, directory_entry->d_name);

            /* Trace. */
            printf("Processing file %s\n", full_filename);

    		/* Time to unificate */
    		char * file_content = read_file(full_filename);

    		if ( file_content != NULL )
    		{
                UnificatorDynamicArray number_list;
                UnificatorDynamicArray duplicate_list;
                unificator_dynamic_array_init(&number_list);
                unificator_dynamic_array_init(&duplicate_list);

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
                        unificator_dynamic_array_push(&number_list, new_element);
                    }
                    else /* Convertion failed. */
                    {
                        printf("Error: Convertion failed for the element %s in the file %s\n", token, full_filename);
                    }

                    token = strtok (NULL, "\n");
                }

                /* Check if we have at least 2 elements. No needed to process otherwise. */
                if ( number_list.size >= 2 )
                {
                    /* Sorting. */
                    unificator_sort_array(number_list.data, number_list.size);

                    /* Find duplicates. */
                    /* We will check each element with the previous one to prevent buffer overflow. */
                    /* That's why we begin the iterating to 1. */
                    for ( size_t i = 1; i < number_list.size; i++ )
                    {
                        if ( number_list.data[i] == number_list.data[i-1] )
                        {
                            /* Duplicates !!!!! */
                            unificator_dynamic_array_push(&duplicate_list, number_list.data[i]);
                        }
                    }

                    /* Sending to the socket. */
                    printf("Timer : %d\n", unificator_timer_get());

                    unificator_dynamic_array_print(&number_list);
                    unificator_dynamic_array_print(&duplicate_list);

                    unificator_dynamic_array_free(&number_list);
                    unificator_dynamic_array_free(&duplicate_list);
                }
    		}
    		else
    		{
    			printf("Error : unable to read the content of the file %s\n", directory_entry->d_name);
    		}

            free(file_content);
    	}
    }
  
    closedir(directory_pointer);     
    return 0; 
} 