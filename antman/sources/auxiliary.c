/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Antman entry point
*/

#include "../include/antman.h"
#include "../include/shared.h"
#include "../include/my_printf.h"

void populate_pool(
    int32_t **array_map, int32_t *pool, uint8_t *my_str, int32_t string_length)
{
    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        *(array_map + i) = pool + i;
    }
    for (int32_t i = 0; i < string_length; i++) {
        *(pool + *(my_str + i)) += 1;
    }
    quicksort(array_map, 0, MAX_ARR_LEN - 1);
}

int32_t compute_length(int32_t **array_map)
{
    int32_t new_length = MAX_ARR_LEN;

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (**(array_map + i) == 0) {
            new_length -= 1;
            continue;
        };
        break;
    }
    return new_length;
}

char *read_file(char **argv, struct stat *st)
{
    char *fcontent = malloc(st->st_size);
    int32_t fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return NULL;
    read(fd, fcontent, st->st_size);
    close(fd);
    return fcontent;
}
