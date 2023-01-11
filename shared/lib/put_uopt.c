/*
** EPITECH PROJECT, 2022
** put_uopt.c
** File description:
** Put uppercase options
*/

#include "../include/my_printf.h"

int put_ntuscfc(double nb)
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
    write_ntfloat(nb, temp, expo, "E");
    return 0;
}

int put_uopt(double nb)
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
        return put_ntuscfc(temp);
    else
        return put_ntfloat(temp);
}
