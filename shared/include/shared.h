#ifndef __SHARED
    #define __SHARED
    #include <stdint.h>
void swap_pointers(uint32_t **ptr_1, uint32_t **ptr_2);
uint32_t split(uint32_t **array, uint32_t low, uint32_t high);
void quicksort(uint32_t **array, uint32_t low, uint32_t high);
#endif
