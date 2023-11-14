#include "shell.h"
#include "funcs.h"

/**
* resetInfo - initializes PassInfo struct
* @_data: struct address
* Return: void nothing
*/
void resetInfo(PassInfo *_data)
{
_data->arg = NULL;
_data->argv = NULL;
_data->path = NULL;
_data->argc = 0;
}

/**
* configInfo - initializes PassInfo struct
* @_data: struct pointer
* @argv: argument vector
*/
void configInfo(PassInfo *_data, char **argv)
{
int i = 0;

_data->ftype = argv[0];
if (_data->arg)
{
_data->argv = splitString(_data->arg, " \t");
if (!_data->argv)
{

_data->argv = malloc(sizeof(char *) * 2);
if (_data->argv)
{
_data->argv[0] = _strdup(_data->arg);
_data->argv[1] = NULL;
}
}
for (i = 0; _data->argv && _data->argv[i]; i++)
;
_data->argc = i;

updateAlias(_data);
updateVars(_data);
}
}

/**
* freeInfo - frees PassInfo struct
* @_data: struct address
* @all: true if freeing all fields
* Return: void
*/
void freeInfo(PassInfo *_data, int all)
{
ffree(_data->argv);
_data->argv = NULL;
_data->path = NULL;
if (all)
{
if (!_data->cmdBuffer)
free(_data->arg);
if (_data->env)
freeStrList(&(_data->env));
if (_data->history)
freeStrList(&(_data->history));
if (_data->alias)
freeStrList(&(_data->alias));
ffree(_data->environ);
_data->environ = NULL;
bfree((void **)_data->cmdBuffer);
if (_data->fileDescriptor > 2)
close(_data->fileDescriptor);
_putchar(CLEAR_BUFFER);
}
}
