/*
** EPITECH PROJECT, 2022
** my_calloc.c
** File description:
** Get memory chunk and init it
*/

#include "../include/shared.h"

// TODO: implement my_malloc 👻
void *my_calloc(unsigned long number, unsigned long size)
{
    char *ptr = malloc(number * size);
    unsigned int index = 0;

    if (!ptr)
        return NULL;
    while (index < number) {
        ptr[index] = 0;
        index = index + 1;
    }
    return ptr;
}
