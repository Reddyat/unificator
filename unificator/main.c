#include <stdio.h> 
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#include "unificator_tools.h"
#include "unificator_dynamic_array.h"
#include "unificator_sort.h"
#include "unificator_timer.h"
#include "unificator_socket.h"

#define FILEPATH_SIZE_MAX 4096

static int keep_running = 1;

void int_handler()
{
    printf("Ctrl-C catched, stopping unificator.\n");
    keep_running = 0;
}

char* read_file(char * filename)
{
    char * buffer = NULL;
    int string_size = 0;
    int read_size = 0;
    FILE *handler = fopen(filename, "r");

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
            }
        }

        fclose(handler);
    }

    return buffer;
}

void help()
{
    printf("Usage : unificator -d <input_directory> -i <ip_address> -p <port>\n");
}

int main(int argc, char ** argv)
{
    /************ SIGNAL MANAGEMENT **************/
    struct sigaction act = {0};
    act.sa_handler = int_handler;
    sigaction(SIGINT, &act, NULL);

    /************ PARSING ARGUMENTS **************/
    char option;
    char * input_directory = NULL;
    char * ip = NULL;
    char * port_value = NULL;
    uint16_t port;

    while ( (option = getopt(argc, argv, "d:i:p:")) != -1 )
    {
        switch ( option )
        {
            case 'd':
                input_directory = optarg;
                break;

            case 'i':
                ip = optarg;
                break;

            case 'p':
                port_value = optarg;
                break;

            case '?':
                if ( optopt == 'd' || optopt == 'i' || optopt == 'p' )
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if ( isprint(optopt) )
                    fprintf(stderr, "Unknown option -%c.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character 0x%x.\n", optopt);

                help();
                return -1;

            default:
                help();
                return -1;
        }   
    }

    if ( input_directory == NULL || ip == NULL || port_value == NULL )
    {
        fprintf(stderr, "Bad arguments : all arguments are mandatory.\n");
        help();
        return -1;
    }

    if ( unificator_string_to_uint16(port_value, &port) != 0 )
    {
        fprintf(stderr, "Bad argument : port value must be > 0 and < 65536.");
        help();
        return -1;
    }

    /* TODO : Check the ip_adress. */

    /*************** LIST AND PROCESS FILES *******************/
    struct dirent * directory_entry;

    DIR * directory_pointer = opendir(input_directory);

    if ( directory_pointer == NULL )
    { 
        printf("Could not open working directory : %s", input_directory); 
        return -1; 
    }

    /* We create and initialize what we need for all the process duration. */
    UnificatorDynamicArray number_list;
    UnificatorDynamicArray duplicate_list;
    unificator_dynamic_array_init(&number_list);
    unificator_dynamic_array_init(&duplicate_list);
    char message[MESSAGE_SIZE_MAX];

    UnificatorSocket socket;
    if ( unificator_socket_init(&socket, ip, port) != 0 )
    {
        fprintf(stderr, "Unable to open the socket, please verify the ip adress you gave in argument.");
        return -1;
    }

    while ( keep_running )
    {
        /* We iterate on all files in the input_directory. */
        while ( (directory_entry = readdir(directory_pointer)) != NULL && keep_running )
        {
            /* We don't process hidden files and the current directory file "." */
            if ( strncmp(directory_entry->d_name, ".", 1) != 0 )
            {
                /* Begining of the process so we start the timer. */
                unificator_timer_start();

                /* Concatenate the directory and the filename. */
                char filepath[FILEPATH_SIZE_MAX];
                snprintf(filepath, FILEPATH_SIZE_MAX, "%s/%s", input_directory, directory_entry->d_name);

                /* Trace. */
                #ifdef DEBUG
                    printf("Processing file %s\n", filepath);
                #endif
                
                /* Time to unificate */
                char * file_content = read_file(filepath);

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
                            unificator_dynamic_array_push(&number_list, new_element);
                        }
                        else /* Convertion failed. */
                        {
                            printf("Error: Convertion failed for the element %s in the file %s\n", token, filepath);
                        }

                        token = strtok(NULL, "\n");
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

                        if ( duplicate_list.size > 0 )
                        {
                            /* Sending to the socket. */
                            unificator_format_message(message, filepath, &duplicate_list, unificator_timer_get());
                            unificator_socket_send(&socket, message, strlen(message) + 1); /* +1 for the \0 */
                        }

                        /* We clear our dynamic array for the next file. */
                        unificator_dynamic_array_clear(&number_list);
                        unificator_dynamic_array_clear(&duplicate_list);
                    }

                    free(file_content);

                    if ( remove(filepath) != 0 )
                    {
                        fprintf(stderr, "Error : Unable to remove the file : %s.\n", filepath);
                    }
                }
                else
                {
                    printf("Error : unable to read the content of the file %s\n", directory_entry->d_name);
                }
            }
        }

        /* We reinitialise the directory pointer because new files were created. */
        rewinddir(directory_pointer);
    }

    /**************** CLEANING *******************/
    unificator_dynamic_array_free(&number_list);
    unificator_dynamic_array_free(&duplicate_list);
    unificator_socket_close(&socket);

    closedir(directory_pointer);     
    return 0; 
} 