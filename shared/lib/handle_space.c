/*
** EPITECH PROJECT, 2022
** handle_space.c
** File description:
** Handle space flag
*/

#include "../include/my_printf.h"

int handle_space(void)
{
    write(1, " ", 1);
    return 1;
}
