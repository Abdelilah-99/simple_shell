#include "shell.h"
/**
 * _atoi - str to int
 * @s: str
 * Return: rslt
 */
int _atoi(char *s)
{
	int i = 0;
	int signe = 1;
	int check = 0;
	unsigned int result = 0;

	while (s[i])
	{
		if (s[i] == '-')
			signe *= -1;
		while (s[i] >= '0' && s[i] <= '9')
		{
			check = 1;
			result = (result * 10) + (s[i] - '0');
			i++;
		}
		if (check == 1)
			break;
		i++;
	}
	result *= signe;
	return (result);
}

/**
 * print_exit - exit function with suc
 * @arr: array
 */
void print_exit(char *arr[])
{
	int i = 0;

	if (arr[1] != NULL)
	{
		if (is_number(arr[1]) == 0)
		{
			_puts("Error: exit argument must be an integer\n");
			exit(2);
		}
		i = _atoi(arr[1]);
	}
	exit(i);
}
/**
 * is_number - check nmbr
 * @str: str
 * Return: 0 or 1
 */
int is_number(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (!_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
/**
 * _isdigit - check for digit
 * @c: whawt we need to check
 * Return: 0 or nmbre
 */
int _isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
