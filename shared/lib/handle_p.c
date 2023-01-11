/*
** EPITECH PROJECT, 2022
** handle_p.c
** File description:
** Handle p flag
*/

#include "../include/my_printf.h"

int handle_p(metadata_t *metadata)
{
    void *ptr = va_arg(*metadata->list, void *);
    int len = put_pointer(ptr);

    return len;
}
