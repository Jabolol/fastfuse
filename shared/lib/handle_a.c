/*
** EPITECH PROJECT, 2022
** handle_a.c
** File description:
** Handle a flag
*/

#include "../include/my_printf.h"

// FIXME: Separate mantissa & format
int handle_a(metadata_t *metadata)
{
    double number = va_arg(*metadata->list, double);
    put_lfhex(number);
    return -1;
}

// FIXME: Create uppercase function
int handle_a_upper(metadata_t *metadata)
{
    double number = va_arg(*metadata->list, double);
    put_lfhex(number);
    return -1;
}
