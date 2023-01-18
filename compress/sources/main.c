/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Antman entry point
*/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/shared.h"
#include "../include/my_printf.h"

void min_heap(leaf_t **leaf_array, int32_t count, int32_t index)
{
    int32_t smallest = index;
    int32_t left = 2 * index + 1;
    int32_t rght = 2 * index + 2;

    if (left < count
        && (*(leaf_array + left))->count < (*(leaf_array + smallest))->count) {
        smallest = left;
    }
    if (rght < count
        && (*(leaf_array + rght))->count < (*(leaf_array + smallest))->count) {
        smallest = rght;
    }

    if (smallest != index) {
        swap_pointers_leaves(leaf_array + index, leaf_array + smallest);
        min_heap(leaf_array, count, smallest);
    }
}

void traverse_path(leaf_t *node, char **paths, char *buff, int32_t position)
{
    if (node->left == NULL && node->right == NULL) {
        *(paths + node->value) = calloc(position + 1, 1);
        strncpy(*(paths + node->value), buff, position);
    } else {
        *(buff + position) = '0';
        traverse_path(node->left, paths, buff, position + 1);
        *(buff + position) = '1';
        traverse_path(node->right, paths, buff, position + 1);
    }
}

leaf_t **populate_leaves(
    int32_t new_length, int32_t *pool, int32_t *leaf_count)
{
    int32_t len = new_length;
    int32_t max_len = len * (len + 1) / 2;
    leaf_t **leaf_array = calloc(max_len, sizeof(leaf_t *));

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (*(pool + i) > 0) {
            leaf_t *leaf = calloc(1, sizeof(leaf_t));
            leaf->count = *(pool + i);
            leaf->value = i;
            *(leaf_array + *leaf_count) = leaf;
            *leaf_count += 1;
        }
    }

    for (int i = *leaf_count / 2 - 1; i >= 0; i--) {
        min_heap(leaf_array, *leaf_count, i);
    }
    return leaf_array;
}

void build_tree(leaf_t **root, leaf_t **leaf_array, int32_t leaf_count)
{
    while (leaf_count > 1) {
        leaf_t *left = *leaf_array;
        *leaf_array = *(leaf_array + (leaf_count - 1));
        leaf_count -= 1;
        min_heap(leaf_array, leaf_count, 0);

        leaf_t *right = *leaf_array;
        *leaf_array = *(leaf_array + (leaf_count - 1));
        leaf_count -= 1;
        min_heap(leaf_array, leaf_count, 0);

        *root = calloc(1, sizeof(leaf_t));
        (*root)->count = left->count + right->count;
        (*root)->left = left;
        (*root)->right = right;

        *(leaf_array + leaf_count) = *root;
        leaf_count += 1;
        min_heap(leaf_array, leaf_count, leaf_count - 1);
    }
}

void write_header(char **paths, FILE *fstream)
{
    uint8_t byte = 0;
    uint8_t temp = 0;
    int32_t bit_count = 0;

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (*(paths + i) != NULL) {
            temp = i;
            fwrite(&temp, 1, 1, fstream);
            uint64_t len = strlen(*(paths + i));
            for (uint64_t j = 0; j < len; j++) {
                byte = byte << 1;
                if (*(*(paths + i) + j) == '1') {
                    byte = byte | 1;
                }
                bit_count = bit_count + 1;
                if (bit_count == BYTE_LEN) {
                    fwrite(&byte, 1, 1, fstream);
                    bit_count = 0;
                    byte = 0;
                }
            }
            temp = 1;
            fwrite(&temp, 1, 1, fstream);
        }
    }

    if (bit_count > 0) {
        byte = byte << (BYTE_LEN - bit_count);
        fwrite(&byte, 1, 1, fstream);
        bit_count = 0;
        byte = 0;
    }

    temp = 2;
    fwrite(&temp, 1, 1, fstream);
}

void write_payload(char **paths, char *my_str, struct stat *st, FILE *fstream)
{
    uint8_t byte = 0;
    uint8_t temp = 0;
    int32_t bit_count = 0;

    for (int32_t j = 0; j < st->st_size; j++) {
        if (*(paths + *(my_str + j)) != NULL) {
            uint64_t len = strlen(*(paths + *(my_str + j)));
            for (uint64_t i = 0; i < len; i++) {
                byte = byte << 1;
                if (*(*(paths + *(my_str + j)) + i) == '1') {
                    byte = byte | 1;
                }
                bit_count = bit_count + 1;
                if (bit_count == BYTE_LEN) {
                    fwrite(&byte, 1, 1, fstream);
                    bit_count = 0;
                    byte = 0;
                }
            }
        }
    }

    if (bit_count > 0) {
        byte = byte << (BYTE_LEN - bit_count);
        fwrite(&byte, 1, 1, fstream);
    }
}

int main(int argc, char **argv)
{
    if (argc <= 2) {
        printf("Usage: ./antman /path/to/file mode\n");
        return 84;
    }
    struct stat st;
    if (lstat(argv[1], &st) != 0)
        return 84;
    char *bufff = malloc(st.st_size);
    FILE *f = fopen(argv[1], "r");
    fread(bufff, st.st_size, 1, f);
    fclose(f);
    char *my_str = bufff;

    int32_t string_length = strlen(my_str);
    int32_t **array_map = calloc(MAX_ARR_LEN, sizeof(int32_t *));
    int32_t *pool = calloc(MAX_ARR_LEN, sizeof(int32_t));

    for (int i = 0; i < MAX_ARR_LEN; i++) {
        *(array_map + i) = pool + i;
    }

    for (int32_t i = 0; i < string_length; i++) {
        *(pool + (uint8_t) * (my_str + i)) += 1;
    }

    quicksort(array_map, 0, MAX_ARR_LEN - 1);

    int32_t new_length = MAX_ARR_LEN;

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (**(array_map + i) == 0) {
            new_length -= 1;
            continue;
        };
        break;
    }

    int32_t leaf_count = 0;

    leaf_t **leaf_array = populate_leaves(new_length, pool, &leaf_count);

    leaf_t *root = NULL;
    build_tree(&root, leaf_array, leaf_count);

    char **paths = calloc(MAX_ARR_LEN, sizeof(char *));
    char *buff = calloc(MAX_ARR_LEN, 1);

    traverse_path(root, paths, buff, 0);

    FILE *fstream = stdout;
    if (!fstream)
        return -1;

    uint8_t byte = 0;
    uint8_t temp = 0;
    int32_t bit_count = 0;

    write_header(paths, fstream);
    write_payload(paths, my_str, &st, fstream);

    fclose(fstream);
    free(array_map);
    free(pool);
    free(bufff);
    return 0;
}
