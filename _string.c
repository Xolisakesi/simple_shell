#include "shell.h"
#include "funcs.h"

/**
*_isalpha - checks for alphabetic character
*@c: charargcter to input
*Return: 1 if c is alphabetic, 0 otherwise
*/

int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
*_atoi - converts a string to an integer
*@s: the string to be converted
*Return: 0 if no numbers in string, converted numbr otherwise
*/

int _atoi(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0;  s[i] != '\0' && flag != 2; i++)
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

/**
* _strdup - duplicates a string
* @str: string to duplicate
* Return: pointer to the duplicated string
*/
char *_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
*_puts - prints  input string
*@str: pointer to string
*
* Return: Nothing void
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
 * _putchar - Custom function to write a character to
 * the standard output.
 * @c: The character to be written.
 * Return: Always 1.
 */

int _putchar(char c)
{
static int i;
static char buf[BUFFER_SIZE];

if (c == CLEAR_BUFFER || i >= BUFFER_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != CLEAR_BUFFER)
buf[i++] = c;
return (1);
}
