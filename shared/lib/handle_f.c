/*
** EPITECH PROJECT, 2022
** handle_f.c
** File description:
** Handle f flag
*/

#include "../include/my_printf.h"

int handle_f(metadata_t *metadata)
{
    int len = 0;
    double number = va_arg(*metadata->list, double);
    int is_neg = number < 0;

    metadata->int_value = my_pow(10, my_nbrlen((int)number) + 1 + 6 - 1);
    metadata->is_neg = number < 0;
    handle_preflags(metadata, number, &len);
    if (is_neg) {
        write(1, "-", 1);
        number = -number;
    }
    handle_midflags(metadata, number, &len);
    len += put_float(number);
    if (is_neg)
        number = -number;
    if (number < 0)
        len += !(number > 0);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}

int handle_f_upper(metadata_t *metadata)
{
    int len = 0;
    double number = va_arg(*metadata->list, double);
    int is_neg = number < 0;

    metadata->int_value = my_pow(10, my_nbrlen((int)number) + 1 + 6 - 1);
    metadata->is_neg = number < 0;
    handle_preflags(metadata, number, &len);
    if (is_neg) {
        write(1, "-", 1);
        number = -number;
    }
    handle_midflags(metadata, number, &len);
    len += put_float(number);
    if (is_neg)
        number = -number;
    if (number < 0)
        len += !(number > 0);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}
