/*
** EPITECH PROJECT, 2022
** to_unsigned.c
** File description:
** Convert nb to unsigned
*/

#include "../include/my_printf.h"

unsigned int to_unsigned(int nb)
{
    if (nb <= 0)
        return (4294967296 + (nb));
    else
        return nb;
}
