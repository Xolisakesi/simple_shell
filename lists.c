#include "shell.h"
#include "funcs.h"

/**
* add_node - adds a node to the head of the list
* @head: pointer to head node
* @str: str field of node
* @numbr: node index
* Return: list size
*/
String_t *add_node(String_t **head, const char *str, int numbr)
{
String_t *new_head;

if (!head)
return (NULL);
new_head = malloc(sizeof(String_t));
if (!new_head)
return (NULL);
_memset((void *)new_head, 0, sizeof(String_t));
new_head->numbr = numbr;
if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}

/**
* add_node_end - adds a node to the end of the list
* @head: pointer to head node
* @str: str field of node
* @numbr: node index
* Return: list size
*/
String_t *add_node_end(String_t **head, const char *str, int numbr)
{
String_t *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(String_t));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(String_t));
new_node->numbr = numbr;
if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}

/**
* printStrList - prints only the str element of a
* String_t linked list
* @h: pointer to first node
* Return: list size
*/
size_t printStrList(const String_t *h)
{
size_t i = 0;

while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
* delete_node_at_index - deletes node at given index
* @head: pointer to first node
* @index: index of node to be deleted
* Return: 1 on success, 0 on failure
*/
int delete_node_at_index(String_t **head, unsigned int index)
{
String_t *node, *prev_node;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str), free(node);
return (1);
}
node = *head;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str), free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}

/**
* freeStrList - frees all nodes of a list
* @head_ptr: pointer to head node
* Return: void
*/
void freeStrList(String_t **head_ptr)
{
String_t *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str), free(node);
node = next_node;
}
*head_ptr = NULL;
}
