/*
** EPITECH PROJECT, 2022
** my_getnbr
** File description:
** Convert nbr from str to int
*/

int get_sign(char const *str)
{
    int index = 0;
    int minus = 0;
    while (str[index] == '+' || str[index] == '-') {
        if (str[index] == '-')
            minus++;
        index++;
    }
    return (minus % 2 == 0 ? '+' : '-');
}

int is_number(char str)
{
    if (str >= '0' && str <= '9')
        return 1;
    else
        return 0;
}

int my_getnbr(char const *str)
{
    int index = 0;
    long int out = 0;

    while (str[index] != '\0') {
        if (str[index] != '+' && str[index] != '-'
            && is_number(str[index]) == 0)
            break;
        if (is_number(str[index]) == 1) {
            out *= 10;
            out += str[index] - '0';
        }
        index++;
    }
    if (out > 2147483647 || out < -2147483648)
        return 0;
    if (get_sign(str) == '-')
        return out * (-1);
    return out;
}
