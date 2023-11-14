#include "shell.h"
#include "funcs.h"

/**
* errAtoi - converts a string to an integer
* @s: string to be converted
* Return: 0 if no numbrbers in string, otherwise error
*/
int errAtoi(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++;
for (i = 0;  s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
* showError - prints an error message
* @_data: parameter & return _data struct
* @estr: string containing specified error type
* Return: void nothing
*/
void showError(PassInfo *_data, char *estr)
{
putsErr(_data->ftype);
putsErr(": ");
displayInt(_data->currentLine, STDERR_FILENO);
putsErr(": ");
putsErr(_data->argv[0]);
putsErr(": ");
putsErr(estr);
}

/**
* displayInt - prints a decimal numbrber (base 10)
* @input: the input
* @fd: filedescriptor
* Return: number of charcters printed
*/
int displayInt(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = putErrChar;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;

return (count);
}

/**
* numToStr - converts num to string.
* @numbr: numbrber
* @base: base
* @flags: arg flags
* Return: string
*/
char *numToStr(long int numbr, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = numbr;

if (!(flags & TO_UNSIGNED) && numbr < 0)
{
n = -numbr;
sign = '-';

}
array = flags & TO_LOWER_CASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do	{
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
* rmComments - replces first instance of '#' with '\0'
* @buf: address of the string to be modified
* Return: Always 0;
*/
void rmComments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
