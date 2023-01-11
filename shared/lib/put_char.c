/*
** EPITECH PROJECT, 2022
** put_char.c
** File description:
** Useless file, do not use
*/

#include "../include/my_printf.h"

int my_putchar(int c)
{
    write(1, &c, 1);
    return (1);
}
