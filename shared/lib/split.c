/*
** EPITECH PROJECT, 2022
** split.c
** File description:
** split implementation
*/

#include "../include/shared.h"

char **split_str(char const *readonly_str, bool (*fn)(uint8_t const))
{
    char *string = my_strdup(readonly_str);
    uint32_t len = my_strlen(string);
    uint32_t delim_len = 0;
    char **split_string = NULL;
    for (uint32_t i = 0; i < len; i++)
        if (fn(*(string + i))) {
            delim_len += 1;
            *(string + i) = '\0';
        }
    if (delim_len == 0)
        return NULL;
    if (!(split_string = my_calloc(delim_len + 2, sizeof(char **))))
        return NULL;
    for (uint32_t i = 0; i < delim_len + 1; i++) {
        uint32_t substr_len = my_strlen(string) + 1;
        *(split_string + i) = string;
        string = string + substr_len;
    }
    *(split_string + delim_len + 1) = NULL;
    return split_string;
}
