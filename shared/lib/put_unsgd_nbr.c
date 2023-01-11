/*
** EPITECH PROJECT, 2022
** put_unsgd_nbr.c
** File description:
** Put unsigned number to stdout
*/

#include "../include/my_printf.h"

void recurse_and_print_unsgd(unsigned int nb, int (*recurse)(unsigned int))
{
    int mod = (nb % 10);
    nb = (nb - mod) / 10;
    (*recurse)(nb);
    my_putchar(mod + '0');
}

int my_put_unsgd_nbr(unsigned int nb)
{
    if (nb == 0) {
        my_putchar('0');
    }
    if (nb > 0) {
        nb >= 10 ? recurse_and_print_unsgd(nb, &my_put_unsgd_nbr)
        : my_putchar((nb % 10) + '0');
    }
    return (my_nbrlen(nb));
}
