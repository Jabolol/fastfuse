/*
** EPITECH PROJECT, 2022
** handle_i.c
** File description:
** Handle i flag
*/

#include "../include/my_printf.h"

int handle_i(metadata_t *metadata)
{
    int len = 0;
    int number = va_arg(*metadata->list, int);

    metadata->int_value = number;
    metadata->is_neg = number < 0;
    handle_preflags(metadata, number, &len);
    if (number < 0) {
        number = -number;
        len += write(1, "-", 1);
    }
    handle_midflags(metadata, number, &len);
    len += my_put_nbr(number);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}
