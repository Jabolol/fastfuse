/*
** EPITECH PROJECT, 2022
** put_binary.c
** File description:
** Put binary to stdout
*/

#include "../include/my_printf.h"

int put_binary(unsigned int num, int *len)
{
    int condition;

    if (!num)
        return 1;
    put_binary(num >> 1, len);
    *len = *len + 1;
    condition = (num & 1) == 1;
    if (condition)
        my_putchar('1');
    else
        my_putchar('0');
    return 1;
}
