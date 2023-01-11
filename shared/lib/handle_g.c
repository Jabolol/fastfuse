/*
** EPITECH PROJECT, 2022
** handle_g.c
** File description:
** Handle g flag
*/

#include "../include/my_printf.h"

int handle_g(metadata_t *metadata)
{
    int len = 0;
    double number = va_arg(*metadata->list, double);

    metadata->double_value = number;
    metadata->is_neg = number < 0;
    handle_preflags(metadata, number, &len);
    handle_midflags(metadata, number, &len);
    if (number == 0) {
        write(1, "0", 1);
        return 1;
    }
    len += put_lopt(number);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}

// FIXME: Come up w/ another way to call the #
// flag, preferably not blocking the execution
// and just appending content to STDOUT
int handle_g_upper(metadata_t *metadata)
{
    int len = 0;
    double number = va_arg(*metadata->list, double);

    metadata->double_value = number;
    metadata->is_neg = number < 0;
    handle_preflags(metadata, number, &len);
    handle_midflags(metadata, number, &len);
    if (number == 0) {
        write(1, "0", 1);
        return 1;
    }
    len += put_uopt(number);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}
