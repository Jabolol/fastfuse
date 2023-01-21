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
    #define EXIT_ERROR     84
    #include <assert.h>
    #include <fcntl.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <unistd.h>
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
char **split_str(char const *readonly_str, bool (*fn)(uint8_t const));
void *my_calloc(unsigned long number, unsigned long size);
char *my_strncpy(char *dest, char const *src, int n);
int my_strlen(char const *str);
bool check_char(const uint8_t);
void *my_memcpy(void *dest, const void *src, int32_t size);
char *my_strdup(char const *s1);
#endif
