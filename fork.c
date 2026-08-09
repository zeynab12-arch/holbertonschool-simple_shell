#include "shell.h"

/**
 * execute_command - executes a command
 * @args: command arguments
 * Return: void
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *command;

	command = find_command(args[0]);

	if (command == NULL)
	{
		fprintf(stderr, "./shell: 1: %s: not found\n", args[0]);
		return;
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(command);
		return;
	}

	if (pid == 0)
	{
		if (execve(command, args, NULL) == -1)
		{
			perror("./shell");
			free(command);
			exit(1);
		}
	}

	wait(&status);
	free(command);
}
