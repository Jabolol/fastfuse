/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Antman entry point
*/

#include "../include/antman.h"
#include "../include/shared.h"
#include "../include/my_printf.h"

void write_header(char **paths)
{
    uint8_t temp = 0;

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (*(paths + i) != NULL) {
            temp = i;
            write(STDOUT_FILENO, &temp, 1);
            uint64_t len = strlen(*(paths + i));
            write(STDOUT_FILENO, *(paths + i), len);
            temp = SEPARATOR_BYTE;
            write(STDOUT_FILENO, &temp, 1);
        }
    }
    temp = END_BYTE;
    write(STDOUT_FILENO, &temp, 1);
}

void process_byte(char path_bit, uint8_t *byte, int32_t *bit_count)
{
    if (path_bit == '1')
        *byte |= 1;
    *bit_count += 1;
    if (*bit_count == BYTE_LEN) {
        write(STDOUT_FILENO, byte, 1);
        *bit_count = 0;
        *byte = 0;
    }
}

void process_path(
    char **paths, int32_t count, uint8_t *byte, int32_t *bit_count)
{
    if (*(paths + count) != NULL) {
        uint64_t len = my_strlen(*(paths + count));
        for (uint64_t i = 0; i < len; i++, *byte <<= 1)
            process_byte(*(*(paths + count) + i), byte, bit_count);
    }
}

void write_payload(char **paths, uint8_t *my_str, struct stat *st)
{
    uint8_t byte = 0;
    int32_t bit_count = 0;
    for (int32_t j = 0; j < st->st_size; j++)
        process_path(paths, *(my_str + j), &byte, &bit_count);
    if (bit_count > 0) {
        byte <<= (BYTE_LEN - 1 - bit_count);
        write(STDOUT_FILENO, &byte, 1);
    }
}

int32_t write_data(leaf_t *root, uint8_t *my_str, struct stat *st)
{
    char **paths = my_calloc(MAX_ARR_LEN, sizeof(char *));
    char *buff = my_calloc(MAX_ARR_LEN, 1);
    if (paths == NULL || buff == NULL) {
        my_printf("Couldn't allocate memory, aborting...\n");
        return EXIT_ERROR;
    }
    traverse_path(root, paths, buff, 0);
    write_header(paths);
    write_payload(paths, my_str, st);
    free(paths);
    free(buff);
    return 0;
}
