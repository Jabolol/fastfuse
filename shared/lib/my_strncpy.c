/*
** EPITECH PROJECT, 2022
** my_strncpy.c
** File description:
** Copy n chars from str 1 into str 2
*/

#include "../include/my_printf.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int index = 0;

    if (src == NULL || dest == NULL)
        return NULL;
    while (index < n && src[index] != '\0') {
        dest[index] = src[index];
        index = index + 1;
    }
    dest[index] = '\0';
    return dest;
}
