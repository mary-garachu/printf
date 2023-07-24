#include "main.h"
/**
 * _printf - is a function that selects the correct function to print.
 * @format: identifier to look for.
 * Return: the length of the string.
 */
int _printf(const char *format, ...)
{
	int i, printed_chars = 0;
	va_list list;

	if (format == NULL)
	{
		return (-1);
	}

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			putchar(format[i]);
			printed_chars++;
		}
		else
		{
			++i;
			if (format[i] == 'c')
			{
				int c = va_arg(list, int);

				putchar(c);
				printed_chars++;
			}
			else if (format[i] == 's')
			{
				char *str = va_arg(list, char *);

				if (str != NULL)
				{
					while (*str != '\0')
					{
						putchar(*str);
						str++;
						printed_chars++;
					}
				}
			}
			else if (format[i] == '%')
			{
				putchar('%');
				printed_chars++;
			}
		}
	}
	va_end(list);
	return (printed_chars);
}
