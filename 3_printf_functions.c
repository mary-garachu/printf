#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @types: arguments
 * @buffer: array to handle print
 * @flags: specifies flags
 * @width: get width
 * @precision: specifies precision
 * @size: Size specifier
 * Return: printed characters
 */
int print_pointer(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char extr_ch = 0, p = ' ';
	int n = BUFF_SIZE - 2, length = 2, p_start = 1;
	unsigned long naddrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	naddrs = (unsigned long)addrs;

	while (naddrs > 0)
	{
		buffer[n--] = map_to[naddrs % 16];
		naddrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';
	if (flags & F_PLUS)
		extr_ch = '+', length++;
	else if (flags & F_SPACE)
		extr_ch = ' ', length++;

	n++;

	return (write_pointer(buffer, n, length,
		width, flags, p, extr_ch, p_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: arguments
 * @buffer: array to handle print
 * @flags: specifies flags
 * @width: get width
 * @precision: specifies precision
 * @size: Size specifier
 * Return: printed characters
 */
int print_non_printable(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - Prints reverse string.
 * @types: arguments
 * @buffer: array to handle print
 * @flags: specifies flags
 * @width: get width
 * @precision: specifies precision
 * @size: Size specifier
 * Return: printed characters
 */

int print_reverse(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Print a string in rot13.
 * @types: arguments
 * @buffer: array to handle print
 * @flags: specifies flags
 * @width: get width
 * @precision: specifies precision
 * @size: Size specifier
 * Return: printed characters
 */
int print_rot13string(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char a;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				a = out[j];
				write(1, &a, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			a = str[i];
			write(1, &a, 1);
			count++;
		}
	}
	return (count);
}
