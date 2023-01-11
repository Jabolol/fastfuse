/*
** EPITECH PROJECT, 2022
** my_getnbr
** File description:
** Convert nbr from str to int
*/

#include "../include/my_printf.h"

long int my_pow(long int nb, long int p)
{
    if (p == 0)
        return (1);
    if (p < 0)
        return (0);
    return (nb *= my_pow(nb, p - 1));
}
