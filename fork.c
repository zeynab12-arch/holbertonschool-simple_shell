#include "shell.h"

extern int last_status;

/**
 * execute_command - forks and executes a command if it exists
 * @args: argument array
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (!args || !args[0])
		return;

	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "./shell: 1: %s: not found\n", args[0]);
		last_status = 127;
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("./shell");
		exit(1);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}

	free(cmd_path);
}
