#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int _putchar(char c);
int _printf(const char *format, ...);
int do_print(const char *fmt, int *pos, va_list list, char buffer[]);

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

#endif
