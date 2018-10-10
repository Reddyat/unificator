#include <stdio.h> 
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

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

int main(int argc , char ** argv)
{
	//TODO : Take the directory where to read the file as argument
	const char * output_directory = "/home/reddyat/workspace/unificator/working/";

    struct dirent * directory_entry;
  
    DIR * directory_pointer = opendir(output_directory);
  
    if (directory_pointer == NULL)
    { 
        printf("Could not open current directory" ); 
        return 0; 
    } 
  
    while ( (directory_entry = readdir(directory_pointer)) != NULL )
    {
    	/* We don't process hidden files and the current directory file "." */
    	if ( strncmp(directory_entry->d_name, ".", 1) != 0 )
    	{
    		char full_filename[256];
    		strcpy(full_filename, output_directory);
    		strcat(full_filename, directory_entry->d_name);

    		/* Time to unificate */
    		char * file_content = read_file(full_filename);

    		if ( file_content != NULL )
    		{
    			// TODO : Find duplicate number.
    			char * pch;
				pch = strtok (file_content,"\n");
				while (pch != NULL)
  				{
					printf ("%s\n",pch);
					pch = strtok (NULL, "\n");
				}
    		}
    		else
    		{
    			printf("Error : unable to read the content of the file %s\n", directory_entry->d_name);
    		}
    	}
    }
  
    closedir(directory_pointer);     
    return 0; 
} 