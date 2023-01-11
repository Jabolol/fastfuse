/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Pushswap entry point
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void swap_pointers(uint32_t **ptr_1, uint32_t **ptr_2)
{
    *ptr_2 = (uint32_t *) ((intptr_t) *ptr_1 ^ (intptr_t) *ptr_2
        ^ (intptr_t) ((*ptr_1 = *ptr_2)));
}

uint32_t split(uint32_t **array, uint32_t low, uint32_t high)
{
    uint32_t pivot = *array[high];
    uint32_t index = low - 1;

    for (uint32_t j = low; j <= high - 1; j++)
        if (*array[j] <= pivot)
            swap_pointers(&array[++index], &array[j]);
    swap_pointers(&array[index + 1], &array[high]);
    return index + 1;
}

void quicksort(uint32_t **array, uint32_t low, uint32_t high)
{
    if (low >= high)
        return;
    uint32_t pivot_position = split(array, low, high);
    quicksort(array, low, pivot_position - 1);
    quicksort(array, pivot_position + 1, high);
}
