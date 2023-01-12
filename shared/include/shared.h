#ifndef __SHARED
    #define __SHARED
    #include <stdint.h>
void swap_pointers(int32_t **ptr_1, int32_t **ptr_2);
int32_t split(int32_t **array, int32_t low, int32_t high);
void quicksort(int32_t **array, int32_t low, int32_t high);
void _swap_pointers(int32_t *ptr_1, int32_t *ptr_2);
int32_t _split(int32_t *array, int32_t low, int32_t high);
void _quicksort(int32_t *array, int32_t low, int32_t high);
#endif
