/*
** EPITECH PROJECT, 2022
** my_printf.h
** File description:
** Header file
*/

#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef __PRINT_F
    #define __PRINT_F
int my_printf(const char *format, ...);
void handle_print(int *out, const char *format, ...);
void handle_cases(char const *format, int *out, va_list ap);
#endif

#ifndef __STRUCTS
    #define FLAG_LEN 5
    #define __STRUCTS
typedef struct flag {
    char flag;
    int value;
} flag_t;
typedef struct metadata {
    int len;
    char const **format;
    va_list *list;
    long int int_value;
    long double double_value;
    int is_neg;
    flag_t flags[FLAG_LEN];
} metadata_t;
typedef struct tuple {
    char key;
    int (*fn)(metadata_t *);
} tuple_t;
#endif

#ifndef __UTILS
    #define __UTILS
    #define ROUND(x) (x >= 0 ? (int) ((x) + 0.5) : (int) ((x) -0.5))
    #define TRUE     (1 == 1)
    #define FALSE    (!TRUE)
int my_strlen(char const *str);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_putchar(int c);
int my_nbrlen(long signed number);
char *my_revstr(char *str);
char *my_strncpy(char *dest, char const *src, int n);
unsigned int to_unsigned(int nb);
int my_put_unsgd_nbr(unsigned int nb);
void put_nbrs_to_stdout(int nb, int precsn);
void write_float(double nb, double temp, int expo, char *letter);
int my_compute_power(int nb, int p);
int put_ntfloat(double nb);
int put_base(unsigned int nb, int base, char *digits);
int put_base_unsigned_long(unsigned long nb, int base, char *digits);
int write_ntfloat(double nb, double temp, int expo, char *letter);
char *get_base(unsigned int nb, int base, char *digits);
int my_getnbr(char const *str);
char *my_strcat(char *dest, char const *src);
int check_flag(metadata_t *metadata, int index, char flag);
int put_ntfloat_g(double nb);
void check_negative(double nb, int *len, double *decimals);
long int my_pow(long int nb, long int p);
#endif

#ifndef __FUNCS
    #define __FUNCS
int put_dec(unsigned int nb);
int put_octal(unsigned int nb);
int put_lhex(unsigned int nb);
int put_uhex(unsigned int nb);
int put_float(double nb);
int put_lscfc(double nb);
int put_uscfc(double nb);
int put_lopt(double nb);
int put_uopt(double nb);
int put_pointer(void *ptr);
int put_lfhex(double nb);
int put_binary(unsigned int nb, int *count);
int put_astr(char *str);
#endif

#ifndef __HANDLERS
    #define __HANDLERS
int handle_c(metadata_t *metadata);
int handle_s(metadata_t *metadata);
int handle_s_upper(metadata_t *metadata);
int handle_d(metadata_t *metadata);
int handle_i(metadata_t *metadata);
int handle_u(metadata_t *metadata);
int handle_o(metadata_t *metadata);
int handle_x(metadata_t *metadata);
int handle_x_upper(metadata_t *metadata);
int handle_e(metadata_t *metadata);
int handle_e_upper(metadata_t *metadata);
int handle_f(metadata_t *metadata);
int handle_f_upper(metadata_t *metadata);
int handle_g(metadata_t *metadata);
int handle_g_upper(metadata_t *metadata);
int handle_p(metadata_t *metadata);
int handle_a(metadata_t *metadata);
int handle_a_upper(metadata_t *metadata);
int handle_b(metadata_t *metadata);
int handle_n(va_list *ap, int *len);
void handle_p_hashtag(unsigned int nb, char *prefix);
int handle_space(void);
int handle_plus(int nb);
int handle_zero(metadata_t *metadata);
int handle_minus(metadata_t *metadata);
void handle_flags(metadata_t *metadata, int number, int *len, char *prefix);
void handle_preflags(metadata_t *metadata, int number, int *len);
void handle_midflags(metadata_t *metadata, int number, int *len);
void handle_postflags(metadata_t *metadata, int number, int *len, char *prefix);
#endif
