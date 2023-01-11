/*
** EPITECH PROJECT, 2022
** put_lfhex.c
** File description:
** Put lowercase float hex
*/

#include "../include/my_printf.h"

long double_to_hex_converter(double nb)
{
    return (*(long *) &nb);
}

int put_lfhex(double nb)
{
    put_base_unsigned_long(
        double_to_hex_converter(nb), 16, "0123456789abcdef");
    return -1;
}
