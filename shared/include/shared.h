#ifndef __SHARED
#define __SHARED
#include <stdint.h>
typedef struct leaf leaf_t;

typedef struct leaf {
    leaf_t *left;
    leaf_t *right;
    int32_t count;
    int32_t value;
} leaf_t;

#define MAX_ARR_LEN 256

void swap_pointers(int32_t **ptr_1, int32_t **ptr_2);
int32_t split(int32_t **array, int32_t low, int32_t high);
void quicksort(int32_t **array, int32_t low, int32_t high);
void swap_pointers_leaves(leaf_t **ptr_1, leaf_t **ptr_2);
#endif
