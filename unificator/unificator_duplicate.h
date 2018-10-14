#ifndef UNIFICATOR_DUPLICATES_H
#define UNIFICATOR_DUPLICATES_H

#include "unificator_dynamic_array.h"

/**
  * @brief Looking for duplicates number in the file <filename> and store it in duplicate_list.
  *        The variable <number_list> is a used for store the numbers contained in the file.
  */
void unificator_find_duplicates(char * filepath,
	UnificatorDynamicArray * number_list, UnificatorDynamicArray * duplicate_list);

/**
  * @brief  Open the file filename and store its content in memory.
  * @return The pointer to the memory containing the file content if succeed,
  *         NULL if failed.
  */
char* _read_file(char * filepath);

#endif /* UNIFICATOR_DUPLICATES_H */