#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

char *find_command(char *command)
{
	char *path;
	char *path_copy;
	char *dir;
	char *full_path;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (command);
		return (NULL);
	}

	path = NULL;
	for (int i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}

	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	char *args[100];
	char *command;
	pid_t pid;
	int status;
	int i;

	while (1)
	{
		printf("(:) ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1)
			break;

		line[strcspn(line, "\n")] = '\0';

		if (line[0] == '\0')
			continue;

		i = 0;
		args[i] = strtok(line, " ");
		while (args[i] != NULL && i < 99)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}

		command = find_command(args[0]);

		if (command == NULL)
		{
			printf("%s: not found\n", args[0]);
			continue;
		}

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			free(command);
			continue;
		}

		if (pid == 0)
		{
			execve(command, args, environ);
			perror("./shell");
			exit(1);
		}

		waitpid(pid, &status, 0);

		if (command != args[0])
			free(command);
	}

	free(line);
	return (0);
}
