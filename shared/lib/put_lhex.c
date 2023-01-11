/*
** EPITECH PROJECT, 2022
** put_lhex.c
** File description:
** Put lowercase hex
*/

#include "../include/my_printf.h"

int put_lhex(unsigned int nb)
{
    return put_base(to_unsigned(nb), 16, "0123456789abcdef");
}
