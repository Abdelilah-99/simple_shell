#include "shell.h"

/**
 * _putchar - writes the character
 * @c: the character to print
 * Return: On success 1.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _strcpy - copy string from source to dest
 * @s: source
 * @d: dest
 * Return: a pointer to dest
 */
char *_strcpy(char *d, const char *s)
{
	int i = 0;

	while (d[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
/**
 * _puts - output  string
 * @str: string
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
/**
 * _getenv - retrieve value of an env var
 * @name: env vari
 * Return: poinster represente the value of the env var
 */
char *_getenv(char *name)
{
	int i = 0;

	for (; environ[i]; i++)
	{
		char *env_name = environ[i];

		if (_strncmp(env_name, name, _strlen(name)) == 0)
		{
			return (_strchr(env_name, '=') + 1);
		}
	}
	return (NULL);
}

/**
 * _strlen - length
 * @s: string
 * Return: length of st
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}
