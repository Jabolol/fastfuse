/*
** EPITECH PROJECT, 2022
** handle_e.c
** File description:
** Handle e flag
*/

#include "../include/my_printf.h"

int handle_e(metadata_t *metadata)
{
    int len = 12;
    double number = va_arg(*metadata->list, double);
    int is_neg = number < 0;

    metadata->int_value = my_pow(10, 12 - 1 + is_neg);
    metadata->is_neg = number < 0;
    handle_preflags(metadata, number, &len);
    if (is_neg) {
        write(1, "-", 1);
        number = -number;
    }
    handle_midflags(metadata, number, &len);
    put_lscfc(number);
    if (is_neg)
        number = -number;
    if (number < 0)
        len += !(number > 0);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}

int handle_e_upper(metadata_t *metadata)
{
    int len = 12;
    double number = va_arg(*metadata->list, double);
    int is_neg = number < 0;

    metadata->int_value = my_pow(10, 12 - 1 + is_neg);
    metadata->is_neg = number < 0;
    handle_preflags(metadata, number, &len);
    if (is_neg) {
        write(1, "-", 1);
        number = -number;
    }
    handle_midflags(metadata, number, &len);
    put_uscfc(number);
    if (is_neg)
        number = -number;
    if (number < 0)
        len += !(number > 0);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}
