/*
** EPITECH PROJECT, 2022
** put_base.c
** File description:
** get_nbr.c with a twist
*/

#include "../include/my_printf.h"

char *get_base(unsigned int nb, int base, char *digits)
{
    char *buff;
    char *temp;
    int count = 0;
    int index = 0;

    if (!(buff = malloc(sizeof(char) * my_nbrlen(nb) + 1)))
        return NULL;
    while (nb != 0) {
        buff[index] = digits[nb % base];
        nb /= base;
        index = index + 1;
        count = count + 1;
    }
    if (!(temp = malloc(sizeof(char) * count + 1)))
        return NULL;
    char *out = my_revstr(my_strncpy(temp, buff, count));
    free(buff);
    return out;
}
