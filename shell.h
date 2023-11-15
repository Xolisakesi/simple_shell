#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

/* my macros */
#define BUFFER_SIZE     1024
#define BUFFER_MAX      4096
#define CLEAR_BUFFER   -1
#define SYST_CMND	0
#define OR_OPER_CMD	1
#define AND_OPER_CMD	2
#define CHAINING_CMD	3
#define TO_LOWER_CASE	1
#define TO_UNSIGNED	2
#define GET_LINE        0
#define TOK_STR         0
#define HSH_HIST        ".hsh_history"

extern char **environ;

/**
* struct StringList - Structure representing a linked
* list node for strings.
* @numbr: Integer value associated with the string.
* @str: Pointer to the character string.
* @next: Pointer to the next node in the linked list.
*/

typedef struct StringList
{
int numbr;
char *str;
struct StringList *next;
} String_t;

/**
* struct passinformation - Structure containing information
* for command execution.
* @argc: Number of arguments.
* @arg: Single argument string.
* @path: Path associated with the command.
* @argv: Array of argument strings.
* @ftype: File type information.
* @histCount: History count.
* @env: Linked list for environment variables.
* @environ: Array of system environment variables.
* @execStatus: Execution status.
* @errorNumber: Error number associated with execution.
* @alias: Linked list for command aliases.
* @env_changed: Flag indicating changes in the environ
* @cmdBuffer: Array of command strings for buffering.
* @lineCountFlag: Flag for counting lines.
* @history: Linked list for command history.
* @cmdBuffer_type: Type of command buffer.
* @fileDescriptor: File descriptor.
* @currentLine: Current line number.
*/

typedef struct passinformation
{
int argc;
char *arg;
char *path;
char **argv;
char *ftype;
int histCount;
String_t *env;
char **environ;
int execStatus;
int errorNumber;
String_t *alias;
int env_changed;
char **cmdBuffer;
int lineCountFlag;
String_t *history;
int cmdBuffer_type;
int fileDescriptor;
unsigned int currentLine;
} PassInfo;


#define DEFAULT_INFO \
{ \
0, NULL, NULL, NULL, NULL, 0, NULL, NULL, 0, \
0, NULL, 0, NULL, 0, NULL, 0, 0, 0 \
}

/**
* struct BuiltinFunction - Represents a built-in
* function.
* @type: The type of the function.
* @fptr: Pointer to the function taking PassInfo*
* as an argument.
*/
typedef struct BuiltinFunction
{
char *type;
int (*fptr)(PassInfo *);
} Builtin_f;
#include "funcs.h"
#endif
