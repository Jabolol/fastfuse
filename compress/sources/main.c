#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shared.h"
#include "../include/my_printf.h"

typedef struct leaf leaf_t;

typedef struct leaf {
    leaf_t *left;
    leaf_t *right;
    uint32_t count;
    uint32_t *value;
} leaf_t;

#define MAX_ARR_LEN 256

int main(void)
{
    char *my_str = "son malos tiempos para estar por soñando";

    uint32_t string_length = strlen(my_str);
    uint32_t **array_map = calloc(MAX_ARR_LEN, sizeof(uint32_t *));
    uint32_t *pool = calloc(MAX_ARR_LEN, sizeof(uint32_t));

    for (int i = 0; i < MAX_ARR_LEN; i++) {
        *(array_map + i) = pool + i;
    }

    for (uint32_t i = 0; i < string_length; i++) {
        *(pool + (uint8_t) * (my_str + i)) += 1;
    }

    quicksort(array_map, 0, MAX_ARR_LEN - 1);

    uint32_t *first_non_zero = NULL;
    uint32_t *last_ordered = pool + MAX_ARR_LEN - 1;
    uint32_t new_length = MAX_ARR_LEN;

    for (uint32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (**(array_map + i) == 0) {
            new_length -= 1;
            continue;
        };
        first_non_zero = *(array_map + i);
        break;
    }

    // for (int i = 0; i < MAX_ARR_LEN; i++) {
    //     printf("index -> [#%d] -> %c: %d\n", i,
    //         (uint8_t) (*(array_map + i) - pool), **(array_map + i));
    // }

    uint32_t level_count = 0;
    leaf_t **leaf_array = NULL;
    leaf_t ***level_array = NULL;
    uint32_t leaves_length = new_length;

    for (; leaves_length != 1;) {
        level_array =
            realloc(level_array, sizeof(uint32_t **) * level_count + 1);
        leaf_array = malloc(sizeof(leaf_t *) * leaves_length);
        for (uint32_t i = 0; i < leaves_length; i++) {
            leaf_t *leaf = malloc(sizeof(leaf_t));
            if (level_count == 0) {
                leaf->count = **(array_map + i);
                leaf->value = NULL;
            } else {
                leaf->count = level_count;
                leaf->value = NULL;
            }
            *(leaf_array + i) = leaf;
        }
        *(level_array + level_count) = leaf_array;
        level_count = level_count + 1;
        leaves_length = (leaves_length / 2) + (leaves_length % 2 == 1);
    }

    /*
    [
     [ 0x 0x 0x 0x ] -> 0  -> {count:  n, value: null ...}[]
        \ /  \ /
     [   0x  0x    ] -> 1  -> {count: -1, value: null ...}[]
          \  /
     [     0x      ] -> 2  -> ...
    ]
    */

    for (uint32_t i = 0, l = new_length; i < level_count;
         i++, l = (l / 2) + (l % 2 == 1)) {
        printf("i -> %d\n", i);
        printf("l -> %d\n", l);
        leaf_t **current_level = *(level_array + i);
        printf("set current_level -> %p\n", current_level);
        if (i + 1 < level_count) {
            printf("#%d index %d < %d\n", i, i + 1, level_count);
            leaf_t **next_level = *(level_array + i + 1);
            printf("set next_level to %p\n", next_level);
            printf("start loop %d -> %d\n", 0, l);
            for (uint32_t j = 0; j < l; j += 2) {
                printf("j -> %d\n", j);
                printf("l -> %d\n", l);
                leaf_t *small = *(current_level + j);
                leaf_t *smaller = *(current_level + j + 1);
                (*(next_level + (uint32_t) (j / 2)))->left = small;
                (*(next_level + (uint32_t) (j / 2)))->right = smaller;
                printf("set next_level[%d]->left -> %p\n", (uint32_t) (j / 2),
                    small);
                printf("set next_level[%d]->right -> %p\n", (uint32_t) (j / 2),
                    smaller);
            }
            printf("end inner loop\n\n");
        } else {
            leaf_t **prev_level = *(level_array + i - 1);
            (*(current_level))->left = *(prev_level);
            printf("set curr_level->left to %p\n", prev_level);
            (*(current_level))->right = *(prev_level + 1);
            printf("set curr_level->right to %p\n", *(prev_level + 1));
        }
    }

    printf("\n");

    for (uint32_t i = 0, l = new_length; i < level_count;
         i++, l = (l / 2) + (l % 2 == 1)) {
        leaf_t **current_level = *(level_array + i);
        for (int k = 0; k < (new_length - l) / 2; k++) {
            write(1, "\t", 1);
        }
        for (uint32_t j = 0; j < l - 1; j += 2) {
            leaf_t *small = *(current_level + j);
            leaf_t *smaller = *(current_level + j + 1);
            printf(" (%d) (%d)", small->count, smaller->count);
            fflush(stdout);
        }
        write(1, "\n\n", 1);
    }

    free(pool);
    free(array_map);
    free(leaf_array);
    free(level_array);
    return 0;
}
