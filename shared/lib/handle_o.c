/*
** EPITECH PROJECT, 2022
** handle_o.c
** File description:
** Handle o flag
*/

#include "../include/my_printf.h"

int handle_o(metadata_t *metadata)
{
    int len = 0;
    unsigned int number = va_arg(*metadata->list, unsigned int);

    metadata->int_value = my_pow(10,
        my_strlen(get_base(to_unsigned(number), 8, "0123456789abcdef")) - 1);
    metadata->is_neg = number < 0;
    if (metadata->flags[4].value == 1)
        metadata->int_value *= 10;
    handle_preflags(metadata, number, &len);
    handle_midflags(metadata, number, &len);
    handle_postflags(metadata, number, &len, "0");
    if (number == 0) {
        write(1, "0", 1);
        handle_postflags(metadata, number, &len, NULL);
        return len + 1;
    }
    len += put_octal(number);
    handle_postflags(metadata, number, &len, NULL);
    return len;
}
