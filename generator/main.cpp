#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char ** argv)
{
   	srand(time(NULL));

	//TODO : Take the directory where to create the file as argument
	const char * output_directory = "/home/reddyat/workspace/unificator/working/";

	for (int i = 1; i < 200; i++)
	{
		/* Convert integer i in string */
		char filename[10];
		sprintf(filename, "%d", i);

		/* Generate the full filename to create */
		char full_filename[256];
		strcpy(full_filename, output_directory);
		strcat(full_filename, filename);

		/* Open the file and fill it with integers !!! */
		FILE * file_pointer = NULL;
		file_pointer = fopen(full_filename, "w");

		if(file_pointer == NULL)
   		{
      		printf("Error : unable to create file %s\n", full_filename);   
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
	}

	return 0;
}