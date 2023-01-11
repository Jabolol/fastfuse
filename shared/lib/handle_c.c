/*
** EPITECH PROJECT, 2022
** handle_c.c
** File description:
** Handle c flag
*/

#include "../include/my_printf.h"

int handle_c(metadata_t *metadata)
{
    char character = va_arg(*metadata->list, int);
    int len = my_putchar(character);
    return len;
}
