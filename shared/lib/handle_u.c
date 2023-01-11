/*
** EPITECH PROJECT, 2022
** handle_u.c
** File description:
** Handle u flag
*/

#include "../include/my_printf.h"

int handle_u(metadata_t *metadata)
{
    int len = 0;
    unsigned int number = va_arg(*metadata->list, unsigned int);

    metadata->int_value =
        my_pow(10, my_nbrlen(to_unsigned(number)) - 1);
    metadata->is_neg = number < 0;
    handle_midflags(metadata, number, &len);
    len += put_dec(number);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}
