/*
** EPITECH PROJECT, 2022
** nbrlen.c
** File description:
** Get nbr length
*/

#include "../include/my_printf.h"

int my_nbrlen(long signed number)
{
    int out = 0;

    if (!number)
        return 1;
    if (number < 0)
        return my_nbrlen(-(number * 10));
    else {
        while (number > 0) {
            number /= 10;
            out = out + 1;
        }
        return out;
    }
    return (-1);
}
