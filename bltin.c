#include "shell.h"
#include "funcs.h"

/**
* unset_alias - sets alias to a string
* @_data: parameter struct
* @str: string alias
* Return: Always 0 on success, 1 on error
*/
int unset_alias(PassInfo *_data, char *str)
{
char *ptr, c;
int retrn;

ptr = _strchr(str, '=');
if (!ptr)
return (1);
c = *ptr;
*ptr = 0;
retrn = delete_node_at_index(&(_data->alias),
get_node_index(_data->alias, node_findPrefix(_data->alias, str, -1)));
*ptr = c;
return (retrn);
}

/**
* set_alias - sets alias to a string
* @_data: parameter struct
* @str: string alias
* Return: Always 0 on success, 1 on error
*/
int set_alias(PassInfo *_data, char *str)
{
char *ptr;

ptr = _strchr(str, '=');
if (!ptr)
return (1);
if (!*++ptr)
return (unset_alias(_data, str));

unset_alias(_data, str);
return (add_node_end(&(_data->alias), str, 0) == NULL);
}

/**
* print_alias - prints  alias string
* @node: alias node
* Return: Always 0 on success, 1 on error
*/
int print_alias(String_t *node)
{
char *ptr = NULL, *a = NULL;

if (node)
{
ptr = _strchr(node->str, '=');
for (a = node->str; a <= ptr; a++)
_putchar(*a), _putchar('\''), _puts(ptr + 1), _puts("'\n");
return (0);
}
return (1);
}

/**
* _showAlias - Custom alias builtin func.
* @_data: Structure containing potential arguments.
*  Return: Always 0
*/
int _showAlias(PassInfo *_data)
{
int i = 0;
char *ptr = NULL;
String_t *node = NULL;

if (_data->argc == 1)
{
node = _data->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; _data->argv[i]; i++)
{
ptr = _strchr(_data->argv[i], '=');
if (ptr)
set_alias(_data, _data->argv[i]);
else
print_alias(node_findPrefix(_data->alias, _data->argv[i], '='));
}

return (0);
}
