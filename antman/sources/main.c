/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** Antman entry point
*/

#include <stdint.h>
#include "../include/antman.h"
#include "../include/shared.h"
#include "../include/my_printf.h"

void process_data(char **argv, struct stat *st, int32_t *exit_code)
{
    char *fcontent = read_file(argv, st);
    int32_t string_length = my_strlen(fcontent);
    uint8_t *my_str = my_calloc(string_length, 1);
    int32_t **array_map = my_calloc(MAX_ARR_LEN, sizeof(int32_t *));
    int32_t *pool = my_calloc(MAX_ARR_LEN, sizeof(int32_t));
    if (my_str == NULL || array_map == NULL || pool == NULL)
        *exit_code = write(1, "Couldn't allocate memory, aborting...\n", 38);
    memcpy(my_str, fcontent, string_length);
    populate_pool(array_map, pool, my_str, string_length);
    int32_t leaf_count = 0;
    leaf_t **leaf_array =
        populate_leaves(compute_length(array_map), pool, &leaf_count);
    leaf_t *root = NULL;
    build_tree(&root, leaf_array, leaf_count);
    write_data(root, my_str, st);
    free(array_map);
    free(my_str);
    free(pool);
    free(fcontent);
}

int main(int argc, char **argv)
{
    if (argc <= 2)
        return 49 + P_ERROR("Usage: ./antman /path/to/file mode\n");
    int32_t mode = my_getnbr(argv[2]);
    if (mode < 0 || mode > 3) {
        return 71 + P_ERROR("Invalid mode\n");
    }
    struct stat st;
    if (lstat(argv[1], &st) != 0 || !S_ISREG(st.st_mode) || st.st_size == 0)
        return EXIT_ERROR;
    int32_t exit_code = 0;
    process_data(argv, &st, &exit_code);
    return exit_code == 0 ? EXIT_SUCCESS : EXIT_ERROR;
}
