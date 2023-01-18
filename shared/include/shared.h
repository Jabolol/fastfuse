/*
** EPITECH PROJECT, 2022
** shared.c
** File description:
** shared include file
*/

#ifndef __SHARED
    #define __SHARED
    #define MAX_ARR_LEN    256
    #define BYTE_LEN       8
    #define SEPARATOR_BYTE 1
    #define END_BYTE       2
    #include <stdint.h>
typedef struct leaf leaf_t;
typedef struct leaf {
    leaf_t *left;
    leaf_t *right;
    int32_t count;
    int32_t value;
} leaf_t;
void swap_pointers(int32_t **ptr_1, int32_t **ptr_2);
int32_t split(int32_t **array, int32_t low, int32_t high);
void quicksort(int32_t **array, int32_t low, int32_t high);
void swap_pointers_leaves(leaf_t **ptr_1, leaf_t **ptr_2);
char **split_str(char const *readonly_str, bool (*fn)(char const));
#endif
