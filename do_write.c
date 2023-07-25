#include "main.h"

/**
 * handle_char - handle the printing of a single character
 * @c: character
 * @buffer: character array to handle print
 * @flags:formatting options
 * @width: width specification
 * @precision: specifies precision
 * @size: represents size
 * Return: character printed
 */

int handle_char(char c, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = 0;
	char p = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		p = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = p;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					 write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}
/**
 * write_number - handle printing of numeric values
 * @is_negative: indicates whether the number is negative
 * @n: number for printing
 * @buffer: character array to handle print
 * @flags:formatting options
 * @width: width specification
 * @precision: specifies precision
 * @size: represents size
 * Return: character printed
 */
int write_number(int is_negative, int n, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - n - 1;
	char p = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(n, buffer, flags, width, precision,
		length, p, extra_ch));
}

/**
 * write_num - handle the printing of a numeric value
 * @n: value to be printed
 * @buffer: character array
 * @flags:formatting options
 * @width: width specification
 * @prec: specifies precision
 * @length: available space
 * @p: padding character
 * @extr_ch: extra character
 * Return: character printed
 */
int write_num(int n, char buffer[], int flags, int width, int prec,
		int length, char p, char extr_ch)
{
	int i, p_start = 1;

	if (prec == 0 && n == BUFF_SIZE - 2 && buffer[n] == '0' && width == 0)
		return (0);
	if (prec == 0 && n == BUFF_SIZE - 2 && buffer[n] == '0')
		buffer[n] = p = ' ';
	if (prec > 0 && prec < length)
		p = ' ';
	while (prec > length)
		buffer[--n] = '0', length++;
	if (extr_ch != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = p;
		buffer[i] = '\0';
		if (flags & F_MINUS && p == ' ')
		{
			if (extr_ch)
				buffer[--n] = extr_ch;
			return (write(1, &buffer[n], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && p == ' ')
		{
			if (extr_ch)
				buffer[--n] = extr_ch;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[n], length));
		}
		else if (!(flags & F_MINUS) && p == '0')
		{
			if (extr_ch)
				buffer[--p_start] = extr_ch;
			return (write(1, &buffer[p_start], i - p_start) + write(1,
						 &buffer[n], length - (1 - p_start)));
		}
	}
	if (extr_ch)
		buffer[--n] = extr_ch;
	return (write(1, &buffer[n], length));
}

/**
 * write_unsgnd - printing of an unsigned numeric value
 * @is_negative: negative number
 * @n: number for printing
 * @buffer: character array
 * @flags: formatting options
 * @width: specifies width
 * @precision: specifies precision
 * @size: rep size
 * Return: printed character
 */
int write_unsgnd(int is_negative int n, char buffer[], int flags, int width,
		int precision, int size)
{
	int length = BUFF_SIZE - n - 1, i = 0;
	char p = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && n == BUFF_SIZE - 2 && buffer[n] == '0')
		return (0);

	if (precision > 0 && precision < length)
		p = ' ';

	while (precision > length)
	{
		buffer[--n] = '\0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = p;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[n], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[n], length));
		}
	}
	return (write(1, &buffer[n], length));
}
/**
 * write_pointer - printing of a pointer value
 * @buffer: character array
 * @n: numeric value
 * @length: available space
 * @width: specify width
 * @flags: formatting option
 * @p: padding character
 * @extr_ch: extra character
 * @p_start: start of an index
 * Return: written characters
 */
int write_pointer(char buffer[], int n, int length, int width,
		int flags, char p, char extr_ch, int p_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = p;
		buffer[i] = '\0';
		if (flags & F_MINUS && p == ' ')
		{
			buffer[--n] = 'x';
			buffer[--n] = '0';
			if (extr_ch)
				buffer[--n] = extr_ch;
			return (write(1, &buffer[n], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && p == ' ')
		{
			buffer[--n] = 'x';
			buffer[--n] = '0';
			if (extr_ch)
				buffer[--n] = extr_ch;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[n], length));
		}
		else if (!(flags & F_MINUS) && p == '0')
		{
			if (extr_ch)
				buffer[--p_start] = extr_ch;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[p_start], i - p_start) +
				write(1, &buffer[n], length - (1 - p_start) - 2));
		}
	}
	buffer[--n] = 'x';
	buffer[--n] = '0';
	if (extr_ch)
		buffer[--n] = extr_ch;
	return (write(1, &buffer[n], BUFF_SIZE - n - 1));
}
