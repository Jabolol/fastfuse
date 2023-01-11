/*
** EPITECH PROJECT, 2022
** handle_space.c
** File description:
** Handle space flag
*/

#include "../include/my_printf.h"

int handle_minus(metadata_t *metadata)
{
    int nb = metadata->flags[2].value;
    int index = 0;

    while (my_nbrlen(metadata->int_value) + index < nb) {
        write(1, " ", 1);
        index = index + 1;
    }

    return index;
}
