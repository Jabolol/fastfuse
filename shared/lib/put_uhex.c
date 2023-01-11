/*
** EPITECH PROJECT, 2022
** put_uhex.c
** File description:
** Put uppercase hex
*/

#include "../include/my_printf.h"

int put_uhex(unsigned int nb)
{
    return put_base(to_unsigned(nb), 16, "0123456789ABCDEF");
}
