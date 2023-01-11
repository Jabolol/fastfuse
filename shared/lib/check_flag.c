/*
** EPITECH PROJECT, 2022
** handle_space.c
** File description:
** Handle space flag
*/

#include "../include/my_printf.h"

int check_flag(metadata_t *metadata, int index, char flag)
{
    return (metadata->flags[index].flag == flag
        && metadata->flags[index].value > -1);
}
