#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void execute_command(char **argv);
char *find_command(char *command);
char **split_line(char *line);
void free_args(char **args);

#endif
