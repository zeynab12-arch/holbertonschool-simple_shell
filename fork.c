#include "shell.h"

/**
 * execute_command - executes a command
 * @args: argument array
 */
void execute_command(char **args)
{
	pid_t pid;
	char *cmd_path;

	if (!args || !args[0])
		return;

	cmd_path = find_command(args[0]);

	if (!cmd_path)
	{
		perror("./hsh");
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}

	free(cmd_path);
}
