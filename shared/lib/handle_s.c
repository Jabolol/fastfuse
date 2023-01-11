/*
** EPITECH PROJECT, 2022
** handle_s.c
** File description:
** Handle s flag
*/

#include "../include/my_printf.h"

int handle_s(metadata_t *metadata)
{
    char *str = va_arg(*metadata->list, char *);

    return my_putstr(str);;
}

int handle_s_upper(metadata_t *metadata)
{
    char *str = va_arg(*metadata->list, char *);

    return put_astr(str);;
}
