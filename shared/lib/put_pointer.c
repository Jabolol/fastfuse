/*
** EPITECH PROJECT, 2022
** put_pointer.c
** File description:
** Put pointer address
*/

#include "../include/my_printf.h"

int put_base_unsigned_long(unsigned long nb, int base, char *digits)
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

int put_pointer(void *ptr)
{
    my_putstr("0x");
    int out =
        put_base_unsigned_long((unsigned long) ptr, 16, "0123456789abcdef");
    return out + 2;
}
