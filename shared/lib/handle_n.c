/*
** EPITECH PROJECT, 2022
** handle_n.c
** File description:
** Handle n flag
*/

#include "../include/my_printf.h"

int handle_n(va_list *ap, int *len)
{
    int *ptr = va_arg(*ap, int *);
    *ptr = *len;
    return 1;
}
