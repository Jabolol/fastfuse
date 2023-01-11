/*
** EPITECH PROJECT, 2022
** put_octal.c
** File description:
** Put octal number
*/

#include "../include/my_printf.h"

int put_octal(unsigned int nb)
{
    int count = put_base(to_unsigned(nb), 8, "0123456789abcdef");
    return count;
}
