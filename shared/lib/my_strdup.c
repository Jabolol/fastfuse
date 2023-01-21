/*
** EPITECH PROJECT, 2022
** my_strcpy.c
** File description:
** Copy str 1 into str 2
*/

#include "../include/shared.h"

char *my_strdup(const char *s1)
{
    int len = my_strlen(s1) + 1;
    char *str = malloc(len);
    if (!str)
        return NULL;
    my_memcpy(str, s1, len);
    return str;
}
