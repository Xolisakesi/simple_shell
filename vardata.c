#include "shell.h"
#include "funcs.h"

/**
* isChainValid - test if current char in buffer is a
* chain delimeter
* @_data: parameter struct
* @buf: char buffer
* @p: pointer to current position in buf
* Return: 1 if chain delimeter, 0 otherwise
*/
int isChainValid(PassInfo *_data, char *buf, size_t *p)
{
size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
_data->cmdBuffer_type = OR_OPER_CMD;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
_data->cmdBuffer_type = AND_OPER_CMD;
}
else if (buf[j] == ';')
{
buf[j] = 0;
_data->cmdBuffer_type = CHAINING_CMD;
}
else
return (0);
*p = j;
return (1);
}

/**
* validateChain - checks we should continue chaining
* based on last execStatus
* @_data: parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
* Return: Void
*/
void validateChain(PassInfo *_data, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (_data->cmdBuffer_type == AND_OPER_CMD)
{
if (_data->execStatus)
{
buf[i] = 0;
j = len;
}
}
if (_data->cmdBuffer_type == OR_OPER_CMD)
{
if (!_data->execStatus)
{
buf[i] = 0;
j = len;
}
}

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
int i = 0;
String_t *node;

for (i = 0; _data->argv[i]; i++)
{
if (_data->argv[i][0] != '$' || !_data->argv[i][1])
continue;

if (!_strcmp(_data->argv[i], "$?"))
{
replaceStr(&(_data->argv[i]),
_strdup(numToStr(_data->execStatus, 10, 0)));
continue;
}
if (!_strcmp(_data->argv[i], "$$"))
{
replaceStr(&(_data->argv[i]),
_strdup(numToStr(getpid(), 10, 0)));
continue;
}
node = node_findPrefix(_data->env, &_data->argv[i][1], '=');
if (node)
{
replaceStr(&(_data->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replaceStr(&_data->argv[i], _strdup(""));

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
