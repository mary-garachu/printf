#include "main.h"

/**
 * do_print - prints argument based on type
 * @fmt: formatted string to print arguments
 * @pos: pointer to an integer variable for current position
 * @list: arguments to be printed
 * @buffer: array to handle print
 * Return: 1 or 2;
 */
int do_print(const char *fmt, int *pos, va_list list, char buffer[])
{
	int iter, chrs_print = 0, printed_chr = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int},
		{'d', print_int}, {'\0', NULL}
	}
	for (iter = 0; fmt_types[iter].fmt != '\0'; iter++)
		if (fmt[*pos] == fmt_types[iter].fmt)
			return (fmt_types[iter].fn(list, buffer));

	if (fmt.types[iter].fmt == '\0')
	{
		if (fmt[*pos] == '\0')
			return (-1);
		chrs_print += write(1, "%%", 1);
		if (fmt[*pos - 1] == ' ')
			chrs_print += write(1, " ", 1);
		chrs_print += write(1, &fmt[*pos], 1);
		return (chrs_print);
	}
	return (chrs_print);
}
