/*
** EPITECH PROJECT, 2022
** handle_space.c
** File description:
** Handle space flag
*/

#include "../include/my_printf.h"

int handle_zero(metadata_t *metadata)
{
    int nb = metadata->flags[3].value;
    int index = 0;

    while ((my_nbrlen(metadata->int_value) + index) < nb) {
        write(1, "0", 1);
        index = index + 1;
    }

    return index;
}
