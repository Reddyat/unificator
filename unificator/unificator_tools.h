#ifndef UNIFICATOR_TOOLS_H
#define UNIFICATOR_TOOLS_H

#include <stdint.h>

/**
  * @brief Convert the <string> input_string in an uint32_t and store it in the variable <converted_value>
  * @return 0 if the conversion succeed, -1 otherwise
  */
int unificator_string_to_uint32(char * input_string, uint32_t * output_value);

#endif /* UNIFICATOR_TOOLS_H */