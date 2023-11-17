#include "shell.h"

/**
 * _is_delmed - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _is_delmed(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _interact_mode - returns true if shell is _interact_mode mode
 * @info: struct address
 *
 * Return: 1 if _interact_mode mode, 0 otherwise
 */
int _interact_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _is_alphed - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _is_alphed(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _slicer - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _slicer(char *s)
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

