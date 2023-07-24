#include "main.h"

void print_buff(char buffer[], int *buff_chrs);

/**
 * _printf - printf function
 * @format: the format
 * Return: printed chr
 */
int _printf(const char *format, ...)
{
	int iter, printed = 0, printed_chr = 0, buff_chrs = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (iter = 0; format && format[iter] != '\0'; iter++)
	{
		if (format[iter] != '%')
		{
			buffer[buff_chrs++] = format[iter];
			if (buff_chrs == BUFF_SIZE)
				print_buff(buffer, &buff_chrs);
			printed_chr++;
		}
		else
		{
			print_buff(buffer, &buff_chrs);
			++iter;
			printed = do_print(format, &iter, list, buffer);
			if (printed == -1)
				return (-1);
			printed_chr += printed;
		}
	}
	print_buff(buffer, &buff_chrs);
	va_end(list);
	return (printed_chr);
}

/**
 * print_buff - prints contents of buffer
 * @buffer: array of characters
 * @buff_chrs: index to add next character/length
 */
void print_buff(char buffer[], int *buff_chrs)
{
	if (*buff_chrs > 0)
		write(1, &buffer[0], *buff_chrs);
	*buff_chrs = 0;
}
