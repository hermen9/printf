#include "main.h"

/**
 * handle_length_modifier - Handle the length modifiers 'l' and 'h'.
 * @format: The format string.
 * @i: Pointer to the current position in the format string.
 * @list: The va_list of arguments.
 * @buffer: The output buffer.
 * @flags: Flags for formatting.
 * @width: The field width.
 * @precision: The precision.
 * @size: Size flag (S_LONG or S_SHORT).
 *
 * Retudrn: The number of characters written to the buffer.
 */
int handle_length_modifier(const char *format, int *i, va_list list,
                           char buffer[], int flags, int width,
                           int precision, int size)
{
	int len = 0;

	if (format[*i] == 'l')
	{
		(*i)++;
		if (format[*i] == 'd' || format[*i] == 'i' || format[*i] == 'u' ||
		    format[*i] == 'o' || format[*i] == 'x' || format[*i] == 'X')
		{
			len += handle_print(format, i, list, buffer, flags, width, precision, size);
		}
		else
		{
			buffer[len++] = '%';
			buffer[len++] = 'l';
			buffer[len++] = format[*i];
		}
	}
	else if (format[*i] == 'h')
	{
		(*i)++;
		if (format[*i] == 'd' || format[*i] == 'i' || format[*i] == 'u' ||
		    format[*i] == 'o' || format[*i] == 'x' || format[*i] == 'X')
		{
			len += handle_print(format, i, list, buffer, flags, width, precision, size);
		}
		else
		{
			buffer[len++] = '%';
			buffer[len++] = 'h';
			buffer[len++] = format[*i];
		}
	}
	else
	{
		buffer[len++] = '%';
		buffer[len++] = format[*i];
	}
	return (len);
}

/**
 * _printf - Our custom printf function.
 * @format: The format string.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	va_list list;
	int i = 0;
	int len = 0;
	char buffer[BUFF_SIZE] = {0};

	va_start(list, format);
	while (format && format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			int flags = get_flags(format, &i);
			int width = get_width(format, &i, list);
			int precision = get_precision(format, &i, list);
			int size = get_size(format, &i);

			len += handle_length_modifier(format, &i, list, buffer, flags, width, precision, size);
		}
		else
		{
			buffer[len++] = format[i];
		}
		i++;
	}
	va_end(list);
	write(1, buffer, len);
	return (len);
}
