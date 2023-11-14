#include "shell.h"
#include "funcs.h"

/**
* get_environ - returns the string array copy of environ
* @_data: Structure containing potential arguments.
* Return: Always 0
*/
char **get_environ(PassInfo *_data)
{
if (!_data->environ || _data->env_changed)
{
_data->environ = String_to_strings(_data->env);
_data->env_changed = 0;
}

return (_data->environ);
}

/**
* _unsetenv - Remove an environment variable
* @_data: Structure containing potential arguments.
* @var: the string env var property
* Return: 1 on delete, 0 otherwise
*/
int _unsetenv(PassInfo *_data, char *var)
{
String_t *node = _data->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = findPrefix(node->str, var);
if (p && *p == '=')
{
_data->env_changed = delete_node_at_index(&(_data->env), i);
i = 0;
node = _data->env;
continue;
}
node = node->next;
i++;
}
return (_data->env_changed);
}

/**
* _setenv - Sets up a new environment variable,
* @_data: Structure containing potential arguments.
* @var: the string env var property
* @value: the string env var value
*  Return: Always 0
*/
int _setenv(PassInfo *_data, char *var, char *value)
{
char *buf = NULL;
String_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = _data->env;
while (node)
{
p = findPrefix(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
_data->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(_data->env), buf, 0);
free(buf);
_data->env_changed = 1;
return (0);
}
