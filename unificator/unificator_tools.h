#ifndef UNIFICATOR_TOOLS_H
#define UNIFICATOR_TOOLS_H

#include <stdint.h>

#include "unificator_dynamic_array.h"

#define MESSAGE_SIZE_MAX 4096


/**
  * @brief Convert the <string> input_string in an uint16_t and store it in the variable <converted_value>
  * @return 0 if the conversion succeed, -1 otherwise
  */
int unificator_string_to_uint16(char * input_string, uint16_t * output_value);

/**
  * @brief Convert the <string> input_string in an uint32_t and store it in the variable <converted_value>
  * @return 0 if the conversion succeed, -1 otherwise
  */
int unificator_string_to_uint32(char * input_string, uint32_t * output_value);

/**
  * @brief Format a message from the filename, the list of duplicates and the processing time. 
  */
void unificator_format_message(char * message, char * filename,
	const UnificatorDynamicArray * duplicates, int processing_time);

#endif /* UNIFICATOR_TOOLS_H */