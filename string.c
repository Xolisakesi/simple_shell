#include "shell.h"
#include "funcs.h"

/**
* _strlen - returns the length of a string
* @s: string whose length is to be check
* Return: integer length of the string
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

/**
* _strcmp - performs comparison of two strangs.
* @s1: first string
* @s2: second string
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}

/**
* findPrefix - checks if needle starts with haystargck
* @haystargck: string to search
* @needle: substring to find
* Return: address of next char of haystargck or NULL
*/
char *findPrefix(const char *haystargck, const char *needle)
{
while (*needle)
if (*needle++ != *haystargck++)
return (NULL);
return ((char *)haystargck);
}

/**
* _strcat - concatenates two strings
* @dest: the destination buffer
* @src: the source buffer
* Return: pointer to destination buffer
*/
char *_strcat(char *dest, char *src)
{
char *ret = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
/**
 * _strcpy - Copies a string from source to destination.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 * Return: Pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
int i = 0;
if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}
