/*
** EPITECH PROJECT, 2022
** put_ntfloat.c
** File description:
** Put float (no trailing nbrs)
*/

#include "../include/my_printf.h"

int put_ntfloat(double nb)
{
    int out = 0;
    float decimals = (nb - (int) nb);
    if (decimals < 0) {
        if ((int) nb == 0)
            out += write(1, "-", 1);
        decimals = -decimals;
    }
    out += my_put_nbr((int) nb);
    if (decimals == 0)
        return out;
    out += my_putchar('.');
    while ((decimals - (int) decimals) <= .99
        && (decimals - (int) decimals) > 0) {
        decimals *= 10;
        if (ROUND(decimals) == 0) {
            out += my_put_nbr(ROUND(decimals));
        }
    }
    out += my_put_nbr(ROUND(decimals));
    return out;
}
