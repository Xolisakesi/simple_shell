#include "shell.h"
#include "funcs.h"

/**
* getLstLen - determines length of linked list
* @h: pointer to first node
* Return: List size
*/
size_t getLstLen(const String_t *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
* String_to_strings - returns an array of strings
* of the list->str
* @head: pointer to first node
* Return: array of strings
*/
char **String_to_strings(String_t *head)
{
String_t *node = head;
size_t i = getLstLen(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}

str = _strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}


/**
* prntLstSize - prints all elements of a String_t
* linked list
* @h: pointer to first node
* Return: size of list
*/
size_t prntLstSize(const String_t *h)
{
size_t i = 0;

while (h)
{
_puts(numToStr(h->numbr, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
* node_findPrefix - returns node whose string
* starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @c: the next character after prefix to match
* Return: match node or null
*/
String_t *node_findPrefix(String_t *node, char *prefix, char c)
{
char *ptr = NULL;

while (node)
{
ptr = findPrefix(node->str, prefix);
if (ptr && ((c == -1) || (*ptr == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
* get_node_index - gets the index of node
* @head: pointer to list head
* @node: pointer to the node
* Return: index of node or -1
*/
ssize_t get_node_index(String_t *head, String_t *node)
{
size_t size = 0;

while (head)
{
if (head == node)
return (size);
head = head->next;
size++;
}
return (-1);
}
