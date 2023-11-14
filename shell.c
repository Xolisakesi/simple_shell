#include "shell.h"
#include "funcs.h"

/**
* main - shell main entry point
* @argc: argument count
* @argv: argument vector
* Return: 0 on success, 1 on error
*/
int main(int argc, char **argv)
{
PassInfo _data[] = { DEFAULT_INFO };

int fd = 2;

fd = fd + 3;

switch (argc)
{
case 2:
{
fd = open(argv[1], O_RDONLY);
if (fd == -1)
{
switch (errno)
{
case EACCES:
exit(126);
case ENOENT:
putsErr(argv[0]);
putsErr(": 0: Can't open ");
putsErr(argv[1]);
putErrChar('\n');
putErrChar(CLEAR_BUFFER);
exit(127);
default:
return (EXIT_FAILURE);
}
}
_data->fileDescriptor = fd;
break;
}
default:
break;
}
fillEnvList(_data);
readHistory(_data);
shellInfo(_data, argv);
return (0);
}

/**
* shellInfo - shell loop
* @_data: parameter & return _data struct
* @argv: argument vector from main()
* Return: 0 on success, 1 on error, or error code
*/
int shellInfo(PassInfo *_data, char **argv)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
resetInfo(_data);
if (interargctInfo(_data))
_puts("$ ");
putErrChar(CLEAR_BUFFER);
r = readInput(_data);
if (r != -1)
{
configInfo(_data, argv);
builtin_ret = locateBuiltin(_data);
if (builtin_ret == -1)
searchCmd(_data);
}
else if (interargctInfo(_data))
_putchar('\n');
freeInfo(_data, 0);
}
writeHistory(_data);
freeInfo(_data, 1);
if (!interargctInfo(_data) && _data->execStatus)
exit(_data->execStatus);
if (builtin_ret == -2)
{
if (_data->errorNumber == -1)
exit(_data->execStatus);
exit(_data->errorNumber);
}
return (builtin_ret);
}

/**
* locateBuiltin - Locates a builtin command
* @_data: the parameter & return PassInfo struct
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* -2 if builtin signals exit
*/
int locateBuiltin(PassInfo *_data)
{
int i, built_in_ret = -1;
Builtin_f builtintbl[] = {
{"exit", _exitHsh},
{"env", _showEnv},
{"help", _showHelp},
{"history", _showHistory},
{"setenv", _setEnv},
{"unsetenv", _unsetEnv},
{"cd", _cd},
{"alias", _showAlias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(_data->argv[0], builtintbl[i].type) == 0)
{
_data->currentLine++;
built_in_ret = builtintbl[i].fptr(_data);
break;
}
return (built_in_ret);
}

/**
* searchCmd - Locates a command in PATH
* @_data: parameter & return _data struct
* Return: void nothing
*/
void searchCmd(PassInfo *_data)
{
char *path = NULL;
int i, k;

_data->path = _data->argv[0];
if (_data->lineCountFlag == 1)
{
_data->currentLine++;
_data->lineCountFlag = 0;
}
for (i = 0, k = 0; _data->arg[i]; i++)
if (!hasDelimiter(_data->arg[i], " \t\n"))
k++;
if (!k)
return;

path = searchPath(_data, _getenv(_data, "PATH="), _data->argv[0]);
if (path)
{
_data->path = path;
runCmdInBckgrnd(_data);
}
else
{
if ((interargctInfo(_data) || _getenv(_data, "PATH=")
|| _data->argv[0][0] == '/') && isValidCmd(_data, _data->argv[0]))
runCmdInBckgrnd(_data);
else if (*(_data->arg) != '\n')
{
_data->execStatus = 127;
showError(_data, "not found\n");
}
}
}

/**
* runCmdInBckgrnd - forks a an exec thread to run cmd
* @_data: parameter & return _data struct
* Return: void nothing
*/
void runCmdInBckgrnd(PassInfo *_data)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(_data->path, _data->argv, get_environ(_data)) == -1)
{
freeInfo(_data, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(_data->execStatus));
if (WIFEXITED(_data->execStatus))
{
_data->execStatus = WEXITSTATUS(_data->execStatus);
if (_data->execStatus == 126)
showError(_data, "permission denied\n");
}
}
}
