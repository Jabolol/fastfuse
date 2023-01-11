/*
** EPITECH PROJECT, 2022
** put_nbr.c
** File description:
** Put nbr to stdout
*/

#include "../include/my_printf.h"

void recurse_and_print(int nb, int (*recurse)(int))
{
    int mod = (nb % 10);
    nb = (nb - mod) / 10;
    (*recurse)(nb);
    my_putchar(mod + '0');
}

int my_put_nbr(int nb)
{
    int out = 0;

    if (nb == 0) {
        my_putchar('0');
    }
    if (nb < 0) {
        my_putchar('-');
        nb = nb * (-1);
        out += 1;
    }
    if (nb > 0) {
        nb >= 10 ? recurse_and_print(nb, &my_put_nbr)
        : my_putchar((nb % 10) + '0');
    }
    return (my_nbrlen(nb) + out);
}
