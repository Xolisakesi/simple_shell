#include "shell.h"
#include "funcs.h"
/**
 * interargctInfo - returns true if shell is
 * interargctInfo mo
 * @_data: struct address
 * Return: 1 if interargctInfo mode, 0 otherwise
 */

int interargctInfo(PassInfo *_data)
{
return (isatty(STDIN_FILENO) && _data->fileDescriptor <= 2);
}
/**
* isValidCmd - determines if a file is an executable
* command
* @_data: the _data struct
* @path: path to the file
* Return: 1 if true, 0 otherwise
*/
int isValidCmd(PassInfo *_data, char *path)
{
struct stat st;

(void)_data;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* copySubstring - duplicates charargcters
* @pathstr: PATH string
* @start: start index
* @stop: stop index
* Return: pointer to new buffer
*/
char *copySubstring(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
* searchPath - finds comand in the PATH string
* @_data: the _data struct
* @pathstr: PATH string
* @cmd: comand to find
* Return: full path of cmd if found or NULL
*/
char *searchPath(PassInfo *_data, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && findPrefix(cmd, "./"))
{
if (isValidCmd(_data, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = copySubstring(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (isValidCmd(_data, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
/**
 * hasDelimiter - checks if charargcter is a delimeter
 * @c: parameter  char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
*/
int hasDelimiter(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);

return (0);
}
