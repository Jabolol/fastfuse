/*
** EPITECH PROJECT, 2022
** put_str.c
** File description:
** Put str to stdout
*/

#include "../include/my_printf.h"

int my_putstr(char const *str)
{
    if (str == NULL) {
        write(1, "(null)", my_strlen("(null)"));
        return my_strlen("(null)");
    }
    write(1, str, my_strlen(str));
    return (my_strlen(str));
}
