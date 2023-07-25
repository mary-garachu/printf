#include "main.h"

/**
 * do_print - prints argument based on type
 * @fmt: formatted string to print arguments
 * @pos: pointer to an integer variable for current position
 * @list: arguments to be printed
 * @buffer: array to handle print
 * @flags: calculate active flags
 * @width: gets width
 * @precision: precision specification
 * @size: specify size
 * Return: 1 or 2;
 */
int do_print(const char *fmt, int *n, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int iter, chrs_print = 0, printed_chr = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'0', print octal}, {'x', print_hexadecimal}
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (iter = 0; fmt_types[iter].fmt != '\0'; iter++)
		if (fmt[*n] == fmt_types[iter].fmt)
			return (fmt_types[iter].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[iter].fmt == '\0')
	{
		if (fmt[*n] == '\0')
			return (-1);
		chrs_print += write(1, "%%", 1);
		if (fmt[*n - 1] == ' ')
			chrs_print += write(1, " ", 1);
		else if (width)
		{
			--(*n);
			while (fmt[*n] != ' ' && fmt[*n] != '%')
				--(*n);
			if (fmt[*n] == ' ')
				--(*n);
			return (1);
		}
		chrs_print += write(1, &fmt[*n], 1);
		return (chrs_print);
	}
	return (printed_chr);
}
