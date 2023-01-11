/*
** EPITECH PROJECT, 2022
** put_dec.c
** File description:
** Put int in base 10
*/

#include "../include/my_printf.h"

int put_dec(unsigned int nb)
{
    return my_put_unsgd_nbr(to_unsigned(nb));
}
