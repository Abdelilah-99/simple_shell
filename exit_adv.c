#include "shell.h"
/**
 * _atoi - string to integer
 * @s: input
 * Return: int
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
 * adv_exit - adv exit
 * @arr: input
 */
void adv_exit(char *arr[])
{
int i = 0;
if (arr[1] != NULL)
i = _atoi(arr[1]);
exit(i);
}
