#ifndef UNIFICATOR_SORT_H
#define UNIFICATOR_SORT_H

#include <stdint.h>
#include <stdlib.h>

/**
  * @brief Sort an array of uint32_t from the smaller to the higher.
  */
void unificator_sort_array(uint32_t * array, size_t array_size);

/**
  * @brief Compare two uint32_t.
  * @return -1 if left < rigth, 1 if left > rigth, 0 if left == rigth.
  */
int unificator_compare_uint32_t(const void * left_integer, const void * rigth_integer);

#endif /* UNIFICATOR_SORT_H */