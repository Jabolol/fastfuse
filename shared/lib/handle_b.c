/*
** EPITECH PROJECT, 2022
** handle_b.c
** File description:
** Handle b flag
*/

#include "../include/my_printf.h"

int handle_b(metadata_t *metadata)
{
    int len = 0;
    unsigned int number = va_arg(*metadata->list, unsigned int);

    metadata->is_neg = number < 0;
    handle_preflags(metadata, number, &len);
    handle_midflags(metadata, number, &len);
    put_binary(number, &len);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}
