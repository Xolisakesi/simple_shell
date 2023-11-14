#include "shell.h"
#include "funcs.h"

/**
* input_buf - buffers chained commands
* @_data: parameter struct
* @buf: address of buffer
* @len: address of len var
* Return: bytes read
*/
ssize_t input_buf(PassInfo *_data, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*len)
{
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if GET_LINE
r = getline(buf, &len_p, stdin);
#else
r = _getline(_data, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0';
r--;
}
_data->lineCountFlag = 1;
rmComments(*buf);
buildHistoryList(_data, *buf, _data->histCount++);
{
*len = r;
_data->cmdBuffer = buf;
}
}
}
return (r);
}

/**
* readInput - reads input exept newline
* @_data: parameter struct
* Return: bytes read
*/
ssize_t readInput(PassInfo *_data)
{
static char *buf;
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(_data->arg), *p;

_putchar(CLEAR_BUFFER);
r = input_buf(_data, &buf, &len);
if (r == -1)
return (-1);
if (len)
{
j = i;
p = buf + i;

validateChain(_data, buf, &j, i, len);
while (j < len)
{
if (isChainValid(_data, buf, &j))
break;
j++;
}
i = j + 1;
if (i >= len)
{
i = len = 0;
_data->cmdBuffer_type = SYST_CMND;
}
*buf_p = p;
return (_strlen(p));
}
*buf_p = buf;
return (r);
}

/**
* read_buf - reads  buffer
* @_data: parameter struct
* @buf: buffer
* @i: size
* Return: r
*/
ssize_t read_buf(PassInfo *_data, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i)
return (0);
r = read(_data->fileDescriptor, buf, BUFFER_SIZE);
if (r >= 0)
*i = r;
return (r);
}

/**
* _getline - retrives the next line of input from STDIN
* @_data: parameter struct
* @ptr: address of pointer to buffer.
* @length: size of preallocated ptr buffer if not NULL
* Return: s
*/
int _getline(PassInfo *_data, char **ptr, size_t *length)
{
static char buf[BUFFER_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = read_buf(_data, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p)
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
* sigintHandler - blocks ctrl-C
* @sig_numbr: signal number
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_numbr)
{
_puts("\n");
_puts("$ ");
_putchar(CLEAR_BUFFER);
}
