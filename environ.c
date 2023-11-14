#include "shell.h"
#include "funcs.h"

/**
* _showEnv - prints the current shell environment
* @_data: Struct containing potential args.
* Return: Always 0
*/
int _showEnv(PassInfo *_data)
{
printStrList(_data->env);
return (0);
}

/**
* _getenv - gets the value of an environ variable
* @_data: Struct containing potential arguments.
* @type: env var type
* Return: the value
*/
char *_getenv(PassInfo *_data, const char *type)
{
String_t *node = _data->env;
char *p;

while (node)
{
p = findPrefix(node->str, type);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* _setEnv - sets environment variable.
* @_data: Structure containing potential arguments.
*  Return: Always 0
*/
int _setEnv(PassInfo *_data)
{
if (_data->argc != 3)
{
putsErr("Incorrect numbrber of arguements\n");
return (1);
}
if (_setenv(_data, _data->argv[1], _data->argv[2]))
return (0);
return (1);
}

/**
* _unsetEnv - Removes the environment variable
* @_data: Structure containing potential arguments.
* Return: Always 0
*/
int _unsetEnv(PassInfo *_data)
{
int i;

if (_data->argc == 1)
{
putsErr("Too few arguements.\n");
return (1);
}
for (i = 1; i <= _data->argc; i++)
_unsetenv(_data, _data->argv[i]);

return (0);
}

/**
* fillEnvList - fills env linked list
* @_data: Structure containing potential arguments.
* Return: Always 0
*/
int fillEnvList(PassInfo *_data)
{
String_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
_data->env = node;
return (0);
}
