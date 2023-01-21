/*
** EPITECH PROJECT, 2022
** shared.c
** File description:
** shared include file
*/

#include "./shared.h"

#ifndef __ANTMAN
    #define __ANTMAN
void min_heap(leaf_t **leaf_array, int32_t count, int32_t index);
void traverse_path(leaf_t *node, char **paths, char *buff, int32_t position);
void build_tree(leaf_t **root, leaf_t **leaf_array, int32_t leaf_count);
leaf_t **populate_leaves(
    int32_t new_length, int32_t *pool, int32_t *leaf_count);
void write_header(char **paths);
char *read_file(char **argv, struct stat *st);
void write_payload(
    char **paths, uint8_t *my_str, struct stat *st);
void populate_pool(int32_t **array_map, int32_t *pool, uint8_t *my_str,
    int32_t string_length);
int32_t compute_length(int32_t **array_map);
int32_t write_data(leaf_t *root, uint8_t *my_str, struct stat *st);
#endif
