/*
** EPITECH PROJECT, 2022
** put_lopt.c
** File description:
** Put lowercase options
*/

#include "../include/my_printf.h"

int write_ntfloat(double nb, double temp, int expo, char *letter)
{
    int len = put_ntfloat(nb);

    my_putstr(letter);
    if (temp >= 1)
        my_putstr("+");
    else
        my_putstr("-");
    if (expo < 10)
        my_putstr("0");
    my_put_nbr(expo);
    return len;
}

int put_ntlscfc(double nb)
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
    return (write_ntfloat(nb, temp, expo, "e") + 3);
}

int put_lopt(double nb)
{
    int expo = 0;
    double temp = nb;

    if (nb >= 1) {
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
    if ((temp < 0 && expo > 4) || expo >= 5)
        return put_ntlscfc(temp);
    else
        return put_ntfloat(temp);
}
