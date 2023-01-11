/*
** EPITECH PROJECT, 2022
** put_astr.c
** File description:
** Put filtered str to stdout
*/

#include "../include/my_printf.h"

int pad_left(int count)
{
    int index = 0;

    while (index < count) {
        write(1, "0", 1);
        index = index + 1;
    }
    return 0;
}

void dec_to_oct_count(int nb, int *out)
{
    if (nb) {
        dec_to_oct_count(nb / 8, out);
        *out = *out + 1;
    }
}

int handle_non_ascii(char *str, int index)
{
    int len = 0;
    int out = 0;
    dec_to_oct_count(str[index], &len);
    write(1, "\\", 1);
    if (str[index] < 0) {
        str[index] = -(str[index]);
        write(1, "-", 1);
        out += 1;
    }
    if (len < 3) {
        pad_left(3 - len);
        out += 3 - len;
    }
    out += put_octal(str[index]);
    return out;
}

int put_astr(char *str)
{
    int index = 0;
    int len = 0;

    if (str == NULL) {
        write(1, "(null)", my_strlen("(null)"));
        return my_strlen("(null)");
    }
    while (index < my_strlen(str)) {
        if (str[index] < 37 || str[index] >= 127)
            len += handle_non_ascii(str, index);
        else
            len += my_putchar(str[index]);
        index = index + 1;
    }
    return (len);
}
