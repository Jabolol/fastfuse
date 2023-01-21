/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Antman entry point
*/

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
        *(paths + node->value) = my_calloc(position + 1, 1);
        my_strncpy(*(paths + node->value), buff, position);
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
    leaf_t **leaf_array = my_calloc(max_len, sizeof(leaf_t *));

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (*(pool + i) > 0) {
            leaf_t *leaf = my_calloc(1, sizeof(leaf_t));
            leaf->count = *(pool + i);
            leaf->value = i;
            *(leaf_array + *leaf_count) = leaf;
            *leaf_count += 1;
        }
    }

    for (int32_t i = *leaf_count / 2 - 1; i >= 0; i--) {
        min_heap(leaf_array, *leaf_count, i);
    }
    return leaf_array;
}

void build_tree(leaf_t **root, leaf_t **leaf_array, int32_t leaf_count)
{
    for (; leaf_count > 1;) {
        leaf_t *left = *leaf_array;
        *leaf_array = *(leaf_array + (leaf_count - 1));
        leaf_count -= 1;
        min_heap(leaf_array, leaf_count, 0);

        leaf_t *right = *leaf_array;
        *leaf_array = *(leaf_array + (leaf_count - 1));
        leaf_count -= 1;
        min_heap(leaf_array, leaf_count, 0);

        *root = my_calloc(1, sizeof(leaf_t));
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
    uint8_t temp = 0;

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (*(paths + i) != NULL) {
            temp = i;
            fwrite(&temp, 1, 1, fstream);
            uint64_t len = strlen(*(paths + i));
            fwrite(*(paths + i), 1, len, fstream);
            temp = SEPARATOR_BYTE;
            fwrite(&temp, 1, 1, fstream);
        }
    }
    temp = END_BYTE;
    fwrite(&temp, 1, 1, fstream);
}

void write_payload(
    char **paths, uint8_t *my_str, struct stat *st, FILE *fstream)
{
    uint8_t byte = 0;
    int32_t bit_count = 0;

    for (int32_t j = 0; j < st->st_size; j++) {
        if (*(paths + *(my_str + j)) != NULL) {
            uint64_t len = my_strlen(*(paths + *(my_str + j)));
            for (uint64_t i = 0; i < len; i++, byte <<= 1) {
                if (*(*(paths + *(my_str + j)) + i) == '1') {
                    byte |= 1;
                }
                bit_count += 1;
                if (bit_count == BYTE_LEN) {
                    fwrite(&byte, 1, 1, fstream);
                    bit_count = 0;
                    byte = 0;
                }
            }
        }
    }

    if (bit_count > 0) {
        byte <<= (BYTE_LEN - 1 - bit_count);
        fwrite(&byte, 1, 1, fstream);
    }
}

int main(int argc, char **argv)
{
    if (argc <= 2) {
        my_printf("Usage: ./antman /path/to/file mode\n");
        return 84;
    }
    struct stat st;
    if (lstat(argv[1], &st) != 0)
        return 84;
    char *fcontent = malloc(st.st_size);
    FILE *f = fopen(argv[1], "r");
    fread(fcontent, 1, st.st_size, f);
    fclose(f);

    int32_t string_length = my_strlen(fcontent);
    uint8_t *my_str = my_calloc(string_length, 1);
    memcpy(my_str, fcontent, string_length);
    int32_t **array_map = my_calloc(MAX_ARR_LEN, sizeof(int32_t *));
    int32_t *pool = my_calloc(MAX_ARR_LEN, sizeof(int32_t));

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        *(array_map + i) = pool + i;
    }

    for (int32_t i = 0; i < string_length; i++) {
        *(pool + *(my_str + i)) += 1;
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

    char **paths = my_calloc(MAX_ARR_LEN, sizeof(char *));
    char *buff = my_calloc(MAX_ARR_LEN, 1);

    traverse_path(root, paths, buff, 0);

    write_header(paths, stdout);
    write_payload(paths, my_str, &st, stdout);

    free(array_map);
    free(my_str);
    free(pool);
    free(fcontent);
    return EXIT_SUCCESS;
}
