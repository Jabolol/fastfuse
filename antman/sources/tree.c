/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Antman entry point
*/

#include "../include/shared.h"

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
        if (*(paths + node->value) == NULL)
            return;
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
    if (!leaf_array)
        return NULL;
    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (!(*(pool + i) > 0))
            continue;
        leaf_t *leaf = my_calloc(1, sizeof(leaf_t));
        if (!leaf)
            return NULL;
        leaf->count = *(pool + i);
        leaf->value = i;
        *(leaf_array + *leaf_count) = leaf;
        *leaf_count += 1;
    }
    for (int32_t i = *leaf_count / 2 - 1; i >= 0; i--) {
        min_heap(leaf_array, *leaf_count, i);
    }
    return leaf_array;
}

void build_tree(leaf_t **root, leaf_t **leaf_array, int32_t leaf_count)
{
    if (root == NULL || leaf_array == NULL)
        return;
    for (; leaf_count > 1;) {
        leaf_t *left = *leaf_array;
        *leaf_array = *(leaf_array + (leaf_count - 1));
        leaf_count -= 1;
        min_heap(leaf_array, leaf_count, 0);
        leaf_t *right = *leaf_array;
        *leaf_array = *(leaf_array + (leaf_count - 1));
        leaf_count -= 1;
        min_heap(leaf_array, leaf_count, 0);
        if (!(*root = my_calloc(1, sizeof(leaf_t))))
            return;
        (*root)->count = left->count + right->count;
        (*root)->left = left;
        (*root)->right = right;
        *(leaf_array + leaf_count) = *root;
        leaf_count += 1;
        min_heap(leaf_array, leaf_count, leaf_count - 1);
    }
}
