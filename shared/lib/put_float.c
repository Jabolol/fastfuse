/*
** EPITECH PROJECT, 2022
** put_float.c
** File description:
** Put float to stdout
*/

#include "../include/my_printf.h"

void put_nbrs_to_stdout(int nb, int precsn)
{
    int index = 0;
    while (index < precsn) {
        my_put_nbr(nb);
        index = index + 1;
    }
}

void check_negative(double nb, int *len, double *decimals)
{
    if ((int) nb == 0 && nb < 0)
        *len += write(1, "-", 1);
    *len += my_put_nbr((int) nb) + my_putchar('.');
    if (*decimals < 0)
        *decimals = - *decimals;
}

int put_float(double nb)
{
    int index = 0;
    int nwnb = 0;
    double decimals = (nb - (int) nb) * 1e6;
    int len = 0;

    check_negative(nb, &len, &decimals);
    if (decimals == 0) {
        put_nbrs_to_stdout(0, 6);
        len = (my_nbrlen((int) nb) + 1 + 6);
    } else {
        nwnb = ROUND(decimals);
        while (my_nbrlen(nwnb) + index < 6) {
            len += my_putchar('0');
            index = index + 1;
        }
        len += my_put_nbr(nwnb);
    }
    return len;
}
