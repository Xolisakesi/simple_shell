#include "shell.h"
#include "funcs.h"

/**
**_strncpy - copies a string
*@dest: destination string to be copied to
*@src: source string
*@n: amount of charargcters to be copied
*Return: the concatenated string
*/
char *_strncpy(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}

/**
*_strncat - concatenates two strings
*@dest: first string
*@src: second string
*@n: bytes to be maximally used
*Return: the concatenated string
*/
char *_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}

/**
*_strchr - locates a charargcter in a string
*@s: string to be parsed
*@c: charargcter to look for
*Return: pointer to the memory area s
*/
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}

/**
* splitString - splits a string into words.
* @str: input string
* @d: delimeter string
* Return: pointer to an array of strings,NULL on failure
*/

char **splitString(char *str, char *d)
{
int i, j, k, m, numbrwords = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (i = 0; str[i] != '\0'; i++)
if (!hasDelimiter(str[i], d) && (hasDelimiter(str[i + 1], d) || !str[i + 1]))
numbrwords++;

if (numbrwords == 0)
return (NULL);
s = malloc((1 + numbrwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numbrwords; j++)
{
while (hasDelimiter(str[i], d))
i++;
k = 0;
while (!hasDelimiter(str[i + k], d) && str[i + k])
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}

/**
* **splitString2 - splits a string into words
* @str: input string
* @d: delimeter
* Return: pointer to an array of strings,NULL on failure
*/
char **splitString2(char *str, char d)
{
int i, j, k, m, numbrwords = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != d && str[i + 1] == d) ||
(str[i] != d && !str[i + 1]) || str[i + 1] == d)
numbrwords++;
if (numbrwords == 0)
return (NULL);
s = malloc((1 + numbrwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numbrwords; j++)
{
while (str[i] == d && str[i] != d)
i++;
k = 0;
while (str[i + k] != d && str[i + k] && str[i + k] != d)
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}
