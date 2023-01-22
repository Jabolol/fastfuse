/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Giantman entry point
*/

#include "../include/shared.h"
#include "../include/my_printf.h"

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

char *find_end_byte(char *buff)
{
    char *payload_start = NULL;
    for (int32_t i = 0; *(buff + i) != '\0'; i++) {
        if (*(buff + i) == END_BYTE) {
            payload_start = buff + i + 1;
            break;
        }
    }
    if (!(*(payload_start - 2) == SEPARATOR_BYTE)) {
        my_putstr("Couldn't find `END_BYTE` payload malformed. Aborting.\n");
        return NULL;
    }
    return payload_start;
}

leaf_t *populate_root(char *buff)
{
    leaf_t *root = my_calloc(1, sizeof(leaf_t));
    if (!root)
        return NULL;
    char **pieces = split_str(buff, &check_char);
    if (!pieces)
        return NULL;
    for (int32_t i = 0; *(*(pieces + i)) != END_BYTE; i++) {
        uint8_t letter = *(*(pieces + i));
        int64_t len = my_strlen(*(pieces + i));
        char *substr = my_calloc(len, 1);
        if (!substr)
            return NULL;
        memcpy(substr, *(pieces + i) + 1, len - 1);
        build_tree(root, substr, letter, 0);
        free(substr);
    }
    free(pieces);
    return root;
}

void decode_payload(char *buff, char *payload_start, struct stat *st)
{
    leaf_t *root = populate_root(buff);
    if (!root)
        return;
    leaf_t *leaf = root;
    uint8_t bit = 0;

    for (int64_t i = (payload_start - buff); i < st->st_size; i++) {
        bit = *(buff + i);
        for (uint8_t j = 7; j != UINT8_MAX; j--) {
            leaf = (bit & (1 << j)) != 0 ? leaf->right : leaf->left;
            leaf->value ? write(STDOUT_FILENO, &leaf->value, 1) : 1;
            leaf->value ? leaf = root : NULL;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc <= 2)
        return 43 + my_putstr("Usage: ./giantman /path/to/file.bin mode\n");
    int32_t n = my_getnbr(argv[2]);
    if (n < 0 || n > 3)
        return 64 + my_putstr("Mode must be 1 -> 3\n");
    struct stat st;
    char *buff = NULL;
    int32_t fd = open(argv[1], O_RDONLY);
    if (stat(argv[1], &st) != 0 || st.st_size == 0 || fd < 0
        || !((buff = malloc(st.st_size))) || !S_ISREG(st.st_mode))
        return 71 + my_putstr("Invalid file\n");
    read(fd, buff, st.st_size);
    char *payload_start = find_end_byte(buff);
    if (!payload_start)
        return EXIT_ERROR;
    decode_payload(buff, payload_start, &st);
    free(buff);
    close(fd);
    return EXIT_SUCCESS;
}
