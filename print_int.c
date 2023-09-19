#include "main.h"

/**
 * print_int - Print an integer.
 * @types: The va_list of arguments.
 * @buffer: The output buffer.
 * @flags: Flags for formatting.
 * @width: The field width.
 * @precision: The precision.
 * @size: Size flag (S_LONG or S_SHORT).
 *
 * Return: The number of characters written to the buffer.
 */
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	int num = va_arg(types, int);
	char num_str[BUFF_SIZE];
	int num_len = sprintf(num_str, "%d", num);
	int total_len = num_len;
	int is_negative = (num < 0);
	int padding = (width > num_len) ? width - num_len : 0;

	if (is_negative)
	{
		total_len++;
		padding--;
	}

	if (!(flags & F_MINUS))
	{
		while (padding > 0)
		{
			buffer[total_len - padding] = (flags & F_ZERO) ? '0' : ' ';
			padding--;
		}
	}

	if (is_negative)
	{
		buffer[total_len - num_len - 1] = '-';
	}

	for (int i = 0; i < num_len; i++)
	{
		buffer[total_len - num_len + i] = num_str[i];
	}

	if (flags & F_MINUS)
	{
		while (padding > 0)
		{
			buffer[total_len - padding] = ' ';
			padding--;
		}
	}

	return (total_len);
}
