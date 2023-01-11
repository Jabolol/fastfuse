/*
** EPITECH PROJECT, 2022
** put_lscfc.c
** File description:
** Put lowercase scientific
*/

#include "../include/my_printf.h"

int put_lscfc(double nb)
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
    write_float(nb, temp, expo, "e");
    return 0;
}
