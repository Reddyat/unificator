#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

#include "unificator_dynamic_array.h"
#include "unificator_duplicate.h"
#include "unificator_socket.h"
#include "unificator_tools.h"
#include "unificator_timer.h"
#include "unificator_sort.h"

#define FILEPATH_SIZE_MAX 4096

static int keep_running = 1;

void int_handler()
{
    printf("Ctrl-C catched, stopping unificator.\n");
    keep_running = 0;
}

void help()
{
    printf("Usage : unificator -d <input_directory> -i <ip_address> -p <port>\n");
}

int main(int argc, char ** argv)
{
    /************* SIGNAL HANDLING ***************/
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

    /* Create the directory in all cases. */
    /* TODO : For the moment, we admit that if it fails, the directory already exists.
     * We do not consider a wrong path or bad rights.*/
    mkdir(input_directory, 0777);

    /* TODO: Check the ip address. */

    /*************** DISPLAY **********************/
    printf("Looking for duplicates in the directory %s...\n", input_directory);


    /*************** LIST AND PROCESS FILES *******************/
    struct dirent * directory_entry;

    DIR * directory_pointer = opendir(input_directory);

    if ( directory_pointer == NULL )
    { 
        printf("Could not open working directory : %s\n", input_directory); 
        return -1; 
    }

    /* We create and initialize what we need for all the process duration. */
    UnificatorDynamicArray number_list;
    UnificatorDynamicArray duplicate_list;
    unificator_dynamic_array_init(&number_list);
    unificator_dynamic_array_init(&duplicate_list);
    char message[MESSAGE_SIZE_MAX];
    UnificatorSocket socket;
    struct timeval tv;

    /* Open the socket. */
    if ( unificator_socket_init(&socket, ip, port) != 0 )
    {
        fprintf(stderr, "Unable to open the socket, please verify the ip adress you gave in argument.\n");
        return -1;
    }

    /* Daemon start. */
    while ( keep_running )
    {
        /* We iterate on all files in the input_directory. */
        while ( (directory_entry = readdir(directory_pointer)) != NULL && keep_running )
        {
            /* We don't process hidden files and the current directory file "." */
            if ( strncmp(directory_entry->d_name, ".", 1) != 0 )
            {
                /* Begining of the process so we start the timer. */
                unificator_timer_start(&tv);

                /* Concatenate the directory and the filename. */
                char filepath[FILEPATH_SIZE_MAX];
                snprintf(filepath, FILEPATH_SIZE_MAX, "%s/%s", input_directory, directory_entry->d_name);

                /* Trace. */
                #ifdef DEBUG
                    printf("Processing file %s\n", filepath);
                #endif
    
                /* We effectively process the file. */
                unificator_find_duplicates(filepath, &number_list, &duplicate_list);

                /* And we send the result to the socket if we find duplicates. */
                if ( duplicate_list.size > 0 )
                {
                    /* Sending to the socket. */
                    unificator_format_message(message, filepath, &duplicate_list, unificator_timer_get(&tv));
                    unificator_socket_send(&socket, message, strlen(message) + 1); /* +1 for the \0 */
                }

                /* We clear our dynamic array for the next file. */
                unificator_dynamic_array_clear(&number_list);
                unificator_dynamic_array_clear(&duplicate_list);

                /* And to finish we remove the file to not process it twice or more. */
                if ( remove(filepath) != 0 )
                {
                    fprintf(stderr, "Error : Unable to remove the file : %s.\n", filepath);
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