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
putsErr(argv[0]), putsErr(": 0: Can't open ");
putsErr(argv[1]), putErrChar(10);
putErrChar(CLEAR_BUFFER);
exit(127);
default:
return (1);
}
}
_data->fileDescriptor = fd;
break;
}
default:
break;
}
fillEnvList(_data), readHistory(_data);
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
ssize_t size = 0;
int retBltn = 0;

while (size != -1 && retBltn != -2)
{
resetInfo(_data);
if (interargctInfo(_data))
_puts("$ ");
putErrChar(CLEAR_BUFFER);
size = readInput(_data);
if (size != -1)
{
configInfo(_data, argv);
retBltn = locateBuiltin(_data);
if (retBltn == -1)
searchCmd(_data);
}
else if (interargctInfo(_data))
_putchar(10);
freeInfo(_data, 0);
}
writeHistory(_data);
freeInfo(_data, 1);
if (!interargctInfo(_data) && _data->execStatus)
exit(_data->execStatus);
if (retBltn == -2)
{
if (_data->errorNumber == -1)
exit(_data->execStatus);
exit(_data->errorNumber);
}
return (retBltn);
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
int i, retBltn = -1;
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
retBltn = builtintbl[i].fptr(_data);
break;
}
return (retBltn);
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
pid_t childPid = fork();

if (childPid == -1)
{
perror("Error:");
return;
}
if (childPid == 0)
{
if (execve(_data->path, _data->argv, get_environ(_data)) == -1)
{
freeInfo(_data, 1);
exit(errno == EACCES ? 126 : 1);
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

