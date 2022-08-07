#include "main.h"
/**
 * _printf - format and print data
 * @format: format specified by the user
 *
 * Return: size in bytes of the printed string.
 */
int _printf(const char * const format, ...)
{
	va_list parameters;
	unsigned int i;
	int func;

	if (!format)
		return (-1);

	va_start(parameters, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!format[i + 1])
			{
				_print(-1);
				va_end(parameters);
				return (-1);
			}
			func = fmt(format[i + 1])(parameters);
			if (func == -1)
			{
				va_end(parameters);
				return (-1);
			}
			else
				i = i + 2;
		}
		else
		{
			_print(format[i]);
			i++;
		}
	}
	va_end(parameters);
	return (_print(-1));
}

int _print(char c)
{
	static char buf[SIZE];
	static int count, i, reset;

	if (reset)
	{
		count = 0;
		reset = 0;
	}

	if (c == -1)
	{
		i = 0;
		reset = 1;
		write(1, buf, SIZE);
		return (count + 1);
	}
	else if (i >= SIZE)
	{
		write(1, buf, SIZE);
		for (i = 0; i < SIZE; i++)
			buf[i] = 0;
		i = 0;
		return (0);
	}

	buf[i++] = c;
	count++;
	return (0);
}
