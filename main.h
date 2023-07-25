#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define UNUSED(x) (void) (x)
#define BUFF_SIZE 1024

/* watchout_flags */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* defined_sizes */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - struct op
 * @fmt: the format
 * @fn: function associated
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - struct op
 * @fmt: the format
 * @fmt_t: function associated
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int do_print(const char *fmt, int *iter, va_list list, char buffer[], int flags, int width, int precision, int size)

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)


int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);


int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);


int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int handle_char(char c, char buffer[], int flags, int width,
		int precision, int size);

int write_number(int is_positive, int n, char buffer[], int flags,
		int width, int precision, int size);

int write_num(int n, char bff[], int flags, int width,
		int precision, int length, char p, char extr_ch);

int write_pointer(char buffer[], int n, int length, int width,
		int flags, char p, char extr_ch, int p_start);

int write_unsgnd(int is_negative, int n, char buffer[],
		int flags, int width, int precision, int size);

int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif


