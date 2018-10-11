#ifndef UNIFICATOR_DYNAMIC_ARRAY_H
#define UNIFICATOR_DYNAMIC_ARRAY_H

#include <stdint.h>
#include <stddef.h>

typedef struct UnificatorDynamicArray {
	uint32_t * data;
	size_t size;
	size_t capacity;
} UnificatorDynamicArray;

#define UNIFICATOR_INITIAL_ARRAY_CAPACITY 512

/** 
  * @brief  Initialize a dynamic array with a starting size of 512 uint32_t elements.
  */
void unificator_dynamic_array_init(UnificatorDynamicArray * dynamic_array);

/**
  * @brief  Add a new value to the dynamic_array.
  */
void unificator_dynamic_array_push(UnificatorDynamicArray * dynamic_array, const uint32_t new_value);

/**
  * @brief  Remove all elements in the dynamic_array.
  */
void unificator_dynamic_array_clear(UnificatorDynamicArray * dynamic_array);

/**
  * @brief  Free all the elements of the dynamic_array.
  */
void unificator_dynamic_array_free(UnificatorDynamicArray * dynamic_array);

/**
  * @brief  Print in stdout the content of the dynamic_array, the size and the capacity.
  */
void unificator_dynamic_array_print(UnificatorDynamicArray * dynamic_array);

#endif /* UNIFICATOR_DYNAMIC_ARRAY_H */