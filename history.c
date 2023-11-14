#include "shell.h"
#include "funcs.h"

/**
* retrieveHistoryFile - retrives the history file
* @_data: parameter struct
* Return: allocated string containg history file
*/

char *retrieveHistoryFile(PassInfo *_data)
{
char *buf, *dir;

dir = _getenv(_data, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HSH_HIST) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HSH_HIST);
return (buf);
}

/**
* writeHistory - creates a file, or appends to an
* existing file
* @_data: parameter struct
* Return: 1 on success, else -1
*/
int writeHistory(PassInfo *_data)
{
ssize_t fd;
char *filetype = retrieveHistoryFile(_data);
String_t *node = NULL;

if (!filetype)
return (-1);

fd = open(filetype, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filetype);
if (fd == -1)
return (-1);
for (node = _data->history; node; node = node->next)
{
pritInfd(node->str, fd);
putInfd('\n', fd);
}
putInfd(CLEAR_BUFFER, fd);
close(fd);
return (1);
}

/**
* readHistory - reads history from file
* @_data: parameter struct
* Return: histCount on success, 0 otherwise
*/
int readHistory(PassInfo *_data)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filetype = retrieveHistoryFile(_data);

if (!filetype)
return (0);

fd = open(filetype, O_RDONLY);
free(filetype);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
buildHistoryList(_data, buf + last, linecount++);
last = i + 1;
}
if (last != i)
buildHistoryList(_data, buf + last, linecount++);
free(buf);
_data->histCount = linecount;
while (_data->histCount-- >= BUFFER_MAX)
delete_node_at_index(&(_data->history), 0);
renumbrber_history(_data);
return (_data->histCount);
}

/**
* buildHistoryList - adds entry to a history linked list
* @_data: Structure containing potential arguments.
* @buf: buffer
* @linecount: history linecount, histCount
* Return: Always 0
*/
int buildHistoryList(PassInfo *_data, char *buf, int linecount)
{
String_t *node = NULL;

if (_data->history)
node = _data->history;
add_node_end(&node, buf, linecount);

if (!_data->history)
_data->history = node;
return (0);
}

/**
* renumbrber_history - renumbr the history linked list
* @_data: Structure containing potential arguments.
* Return: the new histCount
*/
int renumbrber_history(PassInfo *_data)
{
String_t *node = _data->history;
int i = 0;

while (node)
{
node->numbr = i++;
node = node->next;
}
return (_data->histCount = i);
}
