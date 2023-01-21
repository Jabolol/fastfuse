/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Giantman entry point
*/

#include "../include/shared.h"
#include "../include/my_printf.h"

bool check_char(uint8_t const str)
{
    return str == SEPARATOR_BYTE;
}

void build_tree(leaf_t *curr_leaf, char *path, uint8_t letter, int32_t index)
{
    if (*(path + index) == '\0') {
        curr_leaf->left = NULL;
        curr_leaf->right = NULL;
        curr_leaf->value = letter;
        curr_leaf->count = -1;
    }
    if (*(path + index) == '1') {
        if (!curr_leaf->right)
            curr_leaf->right = my_calloc(1, sizeof(leaf_t));
        return build_tree(curr_leaf->right, path, letter, index + 1);
    }
    if (*(path + index) == '0') {
        if (!curr_leaf->left)
            curr_leaf->left = my_calloc(1, sizeof(leaf_t));
        return build_tree(curr_leaf->left, path, letter, index + 1);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        my_printf("Usage: ./giantman /path/to/file.bin\n");
        return 84;
    }
    struct stat st;
    if (stat(argv[1], &st) != 0 || st.st_size == 0) {
        my_printf("Invalid file\n");
        return 84;
    }
    FILE *fstream = fopen(argv[1], "rb");
    if (!fstream) {
        my_printf("Couldn't open the file.\n");
        return 84;
    }

    char *buff = malloc(st.st_size);
    fread(buff, 1, st.st_size, fstream);

    char *payload_start = NULL;

    for (int32_t i = 0; *(buff + i) != '\0'; i++) {
        if (*(buff + i) == END_BYTE) {
            payload_start = buff + i + 1;
            break;
        }
    }

    if (!(*(payload_start - 2) == SEPARATOR_BYTE)) {
        my_printf(
            "Couldn't find `END_BYTE` -> payload malformed. Aborting.\n");
        return 84;
    }

    char **pieces = split_str(buff, &check_char);
    leaf_t *root = my_calloc(1, sizeof(leaf_t));
    for (int32_t i = 0; *(*(pieces + i)) != END_BYTE; i++) {
        uint8_t letter = *(*(pieces + i));
        int64_t len = my_strlen(*(pieces + i));
        char *substr = my_calloc(len, 1);
        memcpy(substr, *(pieces + i) + 1, len - 1);
        build_tree(root, substr, letter, 0);
        free(substr);
    }

    leaf_t *leaf = root;
    uint8_t bit = 0;

    for (int64_t i = (payload_start - buff); i < st.st_size; i++) {
        bit = *(buff + i);
        for (uint8_t j = 7; j != UINT8_MAX; j--) {
            leaf = (bit & (1 << j)) != 0 ? leaf->right : leaf->left;
            if (leaf->value) {
                fwrite(&leaf->value, 1, 1, stdout);
                leaf = root;
            }
        }
    }

    free(pieces);
    free(buff);
    fclose(fstream);
    return 0;
}
