
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

int main(void)
{
    struct stat st;
    if (lstat("./assets/pain.ppm", &st) != 0)
        return 0;
    char *bufff = malloc(st.st_size);
    FILE *f = fopen("./assets/pain.ppm", "r");
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

    int32_t len = new_length;
    int32_t max_len = len * (len + 1) / 2;
    leaf_t **leaf_array = calloc(max_len, sizeof(leaf_t *));

    int32_t leaf_count = 0;

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (*(pool + i) > 0) {
            leaf_t *leaf = calloc(1, sizeof(leaf_t));
            leaf->count = *(pool + i);
            leaf->value = i;
            *(leaf_array + leaf_count) = leaf;
            leaf_count += 1;
        }
    }

    for (int i = leaf_count / 2 - 1; i >= 0; i--) {
        min_heap(leaf_array, leaf_count, i);
    }

    leaf_t *root = NULL;

    while (leaf_count > 1) {
        leaf_t *left = *leaf_array;
        *leaf_array = *(leaf_array + (leaf_count - 1));
        leaf_count -= 1;
        min_heap(leaf_array, leaf_count, 0);

        leaf_t *right = *leaf_array;
        *leaf_array = *(leaf_array + (leaf_count - 1));
        leaf_count -= 1;
        min_heap(leaf_array, leaf_count, 0);

        root = calloc(1, sizeof(leaf_t));
        root->count = left->count + right->count;
        root->left = left;
        root->right = right;

        *(leaf_array + leaf_count) = root;
        leaf_count += 1;
        min_heap(leaf_array, leaf_count, leaf_count - 1);
    }

    char **paths = calloc(MAX_ARR_LEN, sizeof(char *));
    char *buff = calloc(MAX_ARR_LEN, 1);

    traverse_path(root, paths, buff, 0);

    FILE *fstream = fopen("./out.bin", "wb");
    if (!fstream)
        return -1;

    for (int j = 0; j < MAX_ARR_LEN; j++) {
        if (*(paths + j) != NULL) {
            printf("%s\n", *(paths + j));
            uint8_t byte = 0;
            int32_t bit_count = 0;

            for (uint64_t i = 0; i < strlen(*(paths + j)); i++) {
                byte = byte << 1;
                if (*(*(paths + j) + i) == '1') {
                    byte = byte | 1;
                }
                bit_count = bit_count + 1;
                if (bit_count == 8) {
                    fwrite(&byte, 1, 1, fstream);
                    bit_count = 0;
                    byte = 0;
                }
            }
            if (bit_count > 0) {
                byte = byte << (8 - bit_count);
                fwrite(&byte, 1, 1, fstream);
            }
        }
    }

    fclose(fstream);
    free(array_map);
    free(pool);
    free(bufff);
}
