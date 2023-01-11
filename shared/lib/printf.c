/*
** EPITECH PROJECT, 2022
** printf.c
** File description:
** Project entry point
*/

#include "../include/my_printf.h"

/*
    TODO: Claim Theo's kebab
*/

tuple_t fn_arr[] = {{'c', &handle_c}, {'s', &handle_s}, {'d', &handle_d},
    {'i', &handle_i}, {'u', &handle_u}, {'o', &handle_o}, {'x', &handle_x},
    {'X', &handle_x_upper}, {'e', &handle_e}, {'E', &handle_e_upper},
    {'f', &handle_f}, {'F', &handle_f_upper}, {'g', &handle_g},
    {'G', &handle_g_upper}, {'p', &handle_p}, {'a', &handle_a},
    {'A', &handle_a_upper}, {'b', &handle_b}, {'S', &handle_s_upper},
    {'!', NULL}};

void fill_flags(char const *format, metadata_t *metadata, int *skip)
{
    int index = 0;
    char flags[FLAG_LEN] = {'+', ' ', '-', '0', '#'};

    while (index < FLAG_LEN) {
        if (flags[index] == *format) {
            flag_t flag = {flags[index], 1};
            if (*format == '0' || *format == '-') {
                format = format + 1;
                flag.value = my_getnbr(format);
                *skip = my_nbrlen(flag.value);
            }
            metadata->len = metadata->len + 1;
            metadata->flags[index] = flag;
        }
        index = index + 1;
    }
}

void fill_metadata(metadata_t *metadata, char const *format, int *len)
{
    while (TRUE) {
        int temp = metadata->len;
        int skip = 0;
        fill_flags(format, metadata, &skip);
        format = format + 1 + skip;
        if (metadata->len == temp)
            break;
        *len = *len + 1 + skip;
    }
}

int find_fn(char const *format, va_list *ap, int *fmt_len)
{
    int index = 0;
    int len = 1;
    metadata_t metadata = {.len = 0,
        .list = ap,
        .format = &format,
        .flags = {{'+', -1}, {' ', -1}, {'-', -1}, {'0', -1}, {'#', -1}}};

    if (*format == 'n')
        return handle_n(ap, fmt_len);
    fill_metadata(&metadata, format, &len);
    format = format + len - 1;
    while (fn_arr[index].fn != NULL) {
        if (fn_arr[index].key == *format) {
            *fmt_len += fn_arr[index].fn(&metadata);
            break;
        }
        index = index + 1;
    }
    return len;
}

int my_printf(const char *format, ...)
{
    int len = 0;
    int fmt_len = 0;
    va_list ap;
    va_start(ap, format);
    while (*format) {
        if (*format != '%') {
            write(1, format++, 1);
            fmt_len = fmt_len + 1;
            continue;
        }
        format = format + 1;
        if (*format == '%') {
            my_putstr("%");
            fmt_len = fmt_len + 1;
        }
        len = find_fn(format, &ap, &fmt_len);
        format = format + len;
    }
    va_end(ap);
    return (fmt_len);
}
