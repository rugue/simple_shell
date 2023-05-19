#include "shell.h"

/**
 * interactive - this helps return true if shell's interactve mode
 * @info: this is struct address
 *
 * Return: this returns 1 if in interactve mode, and 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - this helps check whether character is a delimetre
 * @a: char to check
 * @delim: delimetre string
 * Return: returns 1 if true, 0 for false
 */
int is_delim(char a, char *delim)
{
	while (*delim)
		if (*delim++ == a)
			return (1);
	return (0);
}

/**
 * _isalpha - helps check alphabetic char
 * @a: The char for inputing
 * Return: this returns 1 if c is alphabetic, and 0 otherwise
 */

int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - this helps converts str to int
 * @s: string for conversion
 * Return: this retuns 0 if no numbs in str, convertd numb otherwse
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
