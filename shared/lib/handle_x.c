/*
** EPITECH PROJECT, 2022
** handle_x.c
** File description:
** Handle x flag
*/

#include "../include/my_printf.h"

int handle_x(metadata_t *metadata)
{
    int len = 0;
    unsigned int number = va_arg(*metadata->list, unsigned int);

    metadata->int_value =
        my_pow(10, my_strlen(get_base(number, 16, "0123456789abcdef")) - 1);
    metadata->is_neg = number < 0;
    if (metadata->flags[4].value == 1)
        metadata->int_value *= 100;
    handle_preflags(metadata, number, &len);
    handle_midflags(metadata, number, &len);
    handle_postflags(metadata, number, &len, "0x");
    if (number == 0) {
        write(1, "0", 1);
        handle_postflags(metadata, number, &len, NULL);
        return len + 1;
    }
    len += put_lhex(number);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}

int handle_x_upper(metadata_t *metadata)
{
    int len = 0;
    unsigned int number = va_arg(*metadata->list, unsigned int);

    metadata->int_value =
        my_pow(10, my_strlen(get_base(number, 16, "0123456789ABCDEF")) - 1);
    metadata->is_neg = number < 0;
    if (metadata->flags[4].value == 1)
        metadata->int_value *= 100;
    handle_preflags(metadata, number, &len);
    handle_midflags(metadata, number, &len);
    handle_postflags(metadata, number, &len, "0X");
    if (number == 0) {
        write(1, "0", 1);
        handle_postflags(metadata, number, &len, NULL);
        return len + 1;
    }
    len += put_uhex(number);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}
