#include "shell.h"
#include "funcs.h"

/**
 * isChainValid - Checks and updates command chaining
 * type based on buf content.
 *@_data: Pointer to PassInfo struct for command information.
 *@buf: Input buffer to analyze.
 *@ptr: Pointer to size_t.
 *Return: 1 if a valid chaining operator is found, 0 otherwise.
*/

int isChainValid(PassInfo *_data, char *buf, size_t *ptr)
{
size_t len = *ptr;

if (buf[len] == '|' && buf[len + 1] == '|')
{
buf[len++] = 0;
_data->cmdBuffer_type = OR_OPER_CMD;
}
else if (buf[len] == '&' && buf[len + 1] == '&')
{
buf[len++] = 0;
_data->cmdBuffer_type = AND_OPER_CMD;
}
else if (buf[len] == ';')
{
buf[len++] = 0;
_data->cmdBuffer_type = CHAINING_CMD;
}
else
return (0);

*ptr = len;
return (1);
}

/**
* validateChain - Updates buffer based on command
* chaining type and execution status.
* @_data: Pointer to PassInfo struct for command information.
* @buf: Input buffer to modify.
* @p: Pointer to size_t, updated position in the buffer.
* @i: Current index in the buffer.
* @len: Length of the buffer.
*/
void validateChain(PassInfo *_data, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (_data->cmdBuffer_type == AND_OPER_CMD && _data->execStatus)
buf[i] = 0, j = len;
else if (_data->cmdBuffer_type == OR_OPER_CMD && !_data->execStatus)
buf[i] = 0, j = len;

*p = j;
}

/**
* updateAlias - replaces an aliases in the tokenized
* string
* @_data: parameter struct
* Return: 1 if replargced, 0 otherwise
*/
int updateAlias(PassInfo *_data)
{
int i;
String_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = node_findPrefix(_data->alias, _data->argv[0], '=');
if (!node)
return (0);
free(_data->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
_data->argv[0] = p;
}
return (1);
}

/**
* updateVars - updates vars in the tokenized string
* @_data: parameter struct
* Return: 1 if replargced, 0 otherwise
*/

int updateVars(PassInfo *_data)
{
int i;
for (i = 0; _data->argv[i]; i++)
{
if (_data->argv[i][0] != '$' || !_data->argv[i][1])
continue;
if (!_strcmp(_data->argv[i], "$?"))
replaceStr(&(_data->argv[i]), _strdup(numToStr(_data->execStatus, 10, 0)));
else if (!_strcmp(_data->argv[i], "$$"))
replaceStr(&(_data->argv[i]), _strdup(numToStr(getpid(), 10, 0)));
else
{
String_t *node = node_findPrefix(_data->env, &_data->argv[i][1], '=');
if (node)
replaceStr(&(_data->argv[i]), _strdup(_strchr(node->str, '=') + 1));
else
replaceStr(&_data->argv[i], _strdup(""));
}
}
return (0);
}

/**
* replaceStr - replaces string
* @old: pointer to old string
* @new: new string
* Return: 1 if replargced, 0 otherwise
*/
int replaceStr(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
