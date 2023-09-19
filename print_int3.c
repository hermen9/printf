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
	int num_len = snprintf(num_str, BUFF_SIZE, "%d", num);
	int total_len = num_len;
	int is_negative = (num < 0);

	if (is_negative)
	{
		total_len++;
	}

	int padding = 0;

	if (precision > num_len)
	{
		padding = precision - num_len;
	}

	if (!(flags & F_MINUS)) /* Check for left alignment flag */
	{
		char padding_char = (flags & F_ZERO) ? '0' : ' ';

		while (width > total_len + padding)
		{
			buffer[total_len++] = padding_char;
		}
	}

	if (is_negative)
	{
		buffer[total_len - num_len - 1] = '-';
	}

	for (int i = 0; i < padding; i++) /* Print leading padding characters (if any) */
	{
		buffer[total_len++] = '0';
	}

	for (int i = 0; i < num_len; i++) /* Print the number */
	{
		buffer[total_len++] = num_str[i];
	}

	if (flags & F_MINUS) /* Check for left alignment flag */
	{
		while (width > total_len)
		{
			buffer[total_len++] = ' ';
		}
	}

	return total_len;
}
