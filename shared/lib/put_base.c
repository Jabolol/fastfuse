/*
** EPITECH PROJECT, 2022
** put_base.c
** File description:
** Convert & put to stdout
*/

#include "../include/my_printf.h"

int put_base(unsigned int nb, int base, char *digits)
{
    char *buff;
    char *temp;
    int count = 0;
    int index = 0;

    if (!(buff = malloc(sizeof(char) * my_nbrlen(nb) + 1)))
        return -1;
    while (nb != 0) {
        buff[index] = digits[nb % base];
        nb /= base;
        index = index + 1;
        count = count + 1;
    }
    if (!(temp = malloc(sizeof(char) * count + 1)))
        return -1;
    write(1, my_revstr(my_strncpy(temp, buff, count)), count);
    free(buff);
    free(temp);
    return count;
}
