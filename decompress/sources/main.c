#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/shared.h"
#include "../include/my_printf.h"

bool check_char(char const str) {
    return str == 1;
}

int main(int ac, char **av) {
    struct stat sb;
    stat(av[1], &sb);
    if (ac < 1)
        return (EXIT_FAILURE);
    char *buff = malloc(sizeof(char)* sb.st_size);

    int fd = open(av[1], O_RDONLY);
        if (fd < 1)
        return (EXIT_FAILURE);

    read(fd, buff, sb.st_size);
    int len = 0;
    while (buff[len] != 2) {
        len++;
    }
    char *new_buff = malloc(sizeof(char)*len);

    for (int index = 0; index < len; index++){
        new_buff[index] = buff[index];
    }
    new_buff[len] = '\0';

    char **arr = split_str(new_buff, &check_char);

    printf("%s", *arr);
    close(fd);
    return 0;
}
