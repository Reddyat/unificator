#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <inttypes.h>
#include <signal.h>

#define FILEPATH_SIZE_MAX 4096

static int keep_running = 1;

void int_handler()
{
    printf("Ctrl-C catched, stopping generator.\n");
    keep_running = 0;
}

int main()
{
    struct sigaction act = {0};
    act.sa_handler = int_handler;
    sigaction(SIGINT, &act, NULL);

    srand(time(NULL));

    //TODO : Take the directory where to create the file as argument
    const char * output_directory = "/home/reddyat/workspace/unificator/working";
    uint32_t filename = 0;

    /* TODO : For the moment, we admit that if it fails, the directory already exists.
     * We do not consider a wrong path or bad rights. We will see this later. */
    mkdir(output_directory, 0777);

    while ( keep_running )
    {
        /* Generate the full filename to create */
        char hidden_filepath[FILEPATH_SIZE_MAX];
        char visible_filepath[FILEPATH_SIZE_MAX];
        snprintf(hidden_filepath, FILEPATH_SIZE_MAX, "%s/.%"PRIu32, output_directory, filename);
        snprintf(visible_filepath, FILEPATH_SIZE_MAX, "%s/%"PRIu32, output_directory, filename);

        /* Open the file and fill it with integers !!! */
        FILE * file_pointer = NULL;
        file_pointer = fopen(hidden_filepath, "w");

        if(file_pointer == NULL)
        {
            fprintf(stderr, "Error : unable to create file %s\n", hidden_filepath);   
            return -1;
        }


        for ( int j = 0; j < 5000; j++)
        {
            /* Generate our unsigned integer for filling the file */
            /* TODO : Create a random generator function to reach max of unsigned int */
            uint32_t random = rand();
            fprintf(file_pointer, "%u\n", random);
        }

        fclose(file_pointer);

        /* Let's make the file visible. */
        rename(hidden_filepath, visible_filepath);

        /* New filename. */
        filename++;

        /* You are too fast for unificator, sorry dude. */
        if ( filename % 1000 == 0 )
        {
            sleep(1);
        }
    }

    return 0;
}