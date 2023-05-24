#include "shell.h"

/**
 * _atoi - convesrt string to an integer
 * @s: string
 * Return: returns an integer
 */
int _atoi(char *s)
{
	int i = 0, signe = 1, c = 0;
	unsigned int r = 0;

	while (s[i])
	{
		if (s[i] == '-')
		{
			signe *= -1;
		}
		while (s[i] >= '0' && s[i] <= '9')
		{
			c = 1;
			r = (r * 10) + (s[i] - '0');
			i++;
		}
		if (c == 1)
		{
			break;
		}
		i++;
	}
	r *= signe;
	return (r);
}
/**
 * print_exit - exit function
 */

void print_exit(void)
{
	exit(EXIT_FAILURE);
}
