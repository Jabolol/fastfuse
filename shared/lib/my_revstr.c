/*
** EPITECH PROJECT, 2022
** my_revstr.c
** File description:
** Reverse the given string
*/

#include "../include/my_printf.h"

char *my_revstr(char *str)
{
    int index = 0;
    int len = my_strlen(str);
    char temp;

    if (str == NULL)
        return NULL;
    if (!str || !*str)
        return str;
    while (index < len / 2) {
        temp = str[len - 1 - index];
        str[len - 1 - index] = str[index];
        str[index] = temp;
        index = index + 1;
    }
    str[len] = '\0';
    return str;
}
