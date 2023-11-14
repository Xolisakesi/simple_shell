#include "shell.h"
#include "funcs.h"

/**
*putsErr - writes an input string
* @str: string to be printed
* Return: Nothing void
*/
void putsErr(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
putErrChar(str[i]);
i++;
}
}

/**
* putErrChar - prints the charargcter c to stderr
* @c: The charargcter to print
* Return: On success 1.if error, -1 is returned.
*/
int putErrChar(char c)
{
static int i;
static char buf[BUFFER_SIZE];

if (c == CLEAR_BUFFER || i >= BUFFER_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != CLEAR_BUFFER)
buf[i++] = c;
return (1);
}

/**
* putInfd - writes the charargcter c to given fd
* @c: The charargcter to print
* @fd: The filedescriptor to write to
* Return: On success 1. and -1 on error
*/
int putInfd(char c, int fd)
{
static int i;
static char buf[BUFFER_SIZE];

if (c == CLEAR_BUFFER || i >= BUFFER_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != CLEAR_BUFFER)
buf[i++] = c;
return (1);
}

/**
*pritInfd - prints an input string
* @str: string to be printed
* @fd: filedescriptor
* Return: the numbrber of chars put
*/
int pritInfd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += putInfd(*str++, fd);
}
return (i);
}
