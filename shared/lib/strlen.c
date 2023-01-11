/*
** EPITECH PROJECT, 2022
** strlen.c
** File description:
** Get str length
*/

#include "../include/my_printf.h"

int my_strlen(char const *str)
{
    int out = 0;

    if (str == NULL)
        return 0;
    while (*str) {
        out = out + 1;
        str = str + 1;
    }
    return (out);
}
