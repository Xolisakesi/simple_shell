#include "shell.h"
#include "funcs.h"

/**
* _exitHsh - exits shell
* @_data: Structure containing potential arguments.
*  Return: exits with a given exit execStatus interger
*/
int _exitHsh(PassInfo *_data)
{
int exitcheck;

if (_data->argv[1])
{
exitcheck = errAtoi(_data->argv[1]);
if (exitcheck == -1)
{
_data->execStatus = 2;
showError(_data, "Illegal interger: ");
putsErr(_data->argv[1]), putErrChar(10);
return (1);
}
_data->errorNumber = errAtoi(_data->argv[1]);
return (-2);
}
_data->errorNumber = -1;
return (-2);
}

/**
* _cd - changes the current directory.
* @_data: Structure containing potential arguments.
* Return: Always 0
*/
int _cd(PassInfo *_data)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("Error Getting curent workid directory\n");
if (!_data->argv[1])
{
dir = _getenv(_data, "HOME=");
if (!dir)
chdir_ret =
chdir((dir = _getenv(_data, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(_data->argv[1], "-") == 0)
{
if (!_getenv(_data, "OLDPWD="))
{
_puts(s), _putchar(10);
return (1);
}
_puts(_getenv(_data, "OLDPWD=")), _putchar(10);
chdir_ret =
chdir((dir = _getenv(_data, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(_data->argv[1]);
if (chdir_ret == -1)
{
showError(_data, "can't cd to ");
putsErr(_data->argv[1]), putErrChar(10);
}
else
{
_setenv(_data, "OLDPWD", _getenv(_data, "PWD="));
_setenv(_data, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * _showHelp - Display help information based on the
 * provided PassInfo structure.
 * @_data: Pointer to PassInfo structure.
 * Return: Always 0.
 */

int _showHelp(PassInfo *_data)
{
char **arg_array;

arg_array = _data->argv;
_puts("Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}

/**
* _showHistory - displays the history list
* @_data: Structure containing potential arguments.
*  Return: Always 0
*/
int _showHistory(PassInfo *_data)
{
prntLstSize(_data->history);
return (0);
}
