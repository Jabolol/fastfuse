#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_str(char const *readonly_str, bool (*fn)(char const))
{
    char *string = strdup(readonly_str);
    uint32_t len = strlen(string);
    uint32_t delim_len = 0;
    char **split_string = NULL;
    for (uint32_t i = 0; i < len; i++)
        if (fn(*(string + i))) {
            delim_len += 1;
            *(string + i) = '\0';
        }
    if (delim_len == 0)
        return NULL;
    if (!(split_string = calloc(delim_len + 2, sizeof(char **))))
        return NULL;
    for (uint32_t i = 0; i < delim_len + 1;) {
        uint32_t substr_len = strlen(string) + 1;
        *(split_string + i) = string;
        string = string + substr_len;
        i = i + 1;
    }
    *(split_string + delim_len + 1) = NULL;
    return split_string;
}
