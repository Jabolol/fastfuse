/*
** EPITECH PROJECT, 2022
** put_uscfc.c
** File description:
** Put uppercase scientific
*/

#include "../include/my_printf.h"

void write_float(double nb, double temp, int expo, char *letter)
{
    put_float(nb);
    my_putstr(letter);
    if ((temp <= -1 || temp >= 1) || temp == 0)
        my_putstr("+");
    else
        my_putstr("-");
    if (expo < 10)
        my_putstr("0");
    my_put_nbr(expo);
}

int put_uscfc(double nb)
{
    int expo = 0;
    double temp = nb;

    if (nb < 0) {
        write(1, "-", 1);
        nb = -nb;
    }
    if (nb <= 0 || nb >= 1) {
        while (my_nbrlen((int) nb) > 1) {
            nb = nb / 10;
            expo = expo + 1;
        }
    } else {
        while ((int) nb == 0) {
            nb = nb * 10;
            expo = expo + 1;
        }
    }
    write_float(nb, temp, expo, "E");
    return 0;
}
