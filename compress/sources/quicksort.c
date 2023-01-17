/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Pushswap entry point
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/shared.h"

void swap_pointers(int32_t **ptr_1, int32_t **ptr_2)
{
    *ptr_2 = (int32_t *) ((intptr_t) *ptr_1 ^ (intptr_t) *ptr_2
        ^ (intptr_t) ((*ptr_1 = *ptr_2)));
}

int32_t split(int32_t **array, int32_t low, int32_t high)
{
    int32_t pivot = *array[high];
    int32_t index = low - 1;

    for (int32_t j = low; j <= high - 1; j++)
        if (*array[j] <= pivot)
            swap_pointers(&array[++index], &array[j]);
    swap_pointers(&array[index + 1], &array[high]);
    return index + 1;
}

void quicksort(int32_t **array, int32_t low, int32_t high)
{
    if (low >= high)
        return;
    int32_t pivot_position = split(array, low, high);
    quicksort(array, low, pivot_position - 1);
    quicksort(array, pivot_position + 1, high);
}

void swap_pointers_leaves(leaf_t **ptr_1, leaf_t **ptr_2)
{
    *ptr_2 = (leaf_t *) ((intptr_t) *ptr_1 ^ (intptr_t) *ptr_2
        ^ (intptr_t) ((*ptr_1 = *ptr_2)));
}
