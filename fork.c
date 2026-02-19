#include "shell.h"

extern int last_status;

/**
 * execute_command - executes a command
 * @args: argument array
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (!args || !args[0])
		return;

	/* BUILTIN EXIT */
	if (strcmp(args[0], "exit") == 0)
	{
		exit(last_status);
	}

	cmd_path = find_command(args[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		last_status = 127;
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("./hsh");
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
