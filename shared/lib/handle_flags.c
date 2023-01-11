/*
** EPITECH PROJECT, 2022
** handle_flags.c
** File description:
** Handle all flags
*/

#include "../include/my_printf.h"

void handle_preflags(metadata_t *metadata, int number, int *len)
{
    int index = 0;
    int is_plus = number < 0;

    while (index < FLAG_LEN) {
        if (check_flag(metadata, index, '+') == 1 && !metadata->is_neg) {
            int prev_len = *len;
            *len += handle_plus(number);
            is_plus = !(prev_len == *len);
            metadata->int_value *= 10;
        }
        if (check_flag(metadata, index, ' ') == 1 && is_plus == 0
            && !metadata->is_neg) {
            *len += handle_space();
            metadata->int_value *= 10;
        }
        index = index + 1;
    }
}

void handle_midflags(metadata_t *metadata, int number, int *len)
{
    int index = number - number;

    while (index < FLAG_LEN) {
        if (check_flag(metadata, index, '0') == 1) {
            *len += handle_zero(metadata);
        }
        index = index + 1;
    }
}

void handle_postflags(metadata_t *metadata, int number, int *len, char *prefix)
{
    int index = 0;

    while (index < FLAG_LEN) {
        if (check_flag(metadata, index, '#') == 1 && number != 0
            && prefix != NULL) {
            handle_p_hashtag(number, prefix);
            *len += my_strlen(prefix);
        }
        if (check_flag(metadata, index, '-') == 1 && prefix == NULL)
            *len += handle_minus(metadata);
        index = index + 1;
    }
}
