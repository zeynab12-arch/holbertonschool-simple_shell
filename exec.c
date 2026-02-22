#include "shell.h"

void execute_command(char **argv)
{
	pid_t pid;
	char *cmd_path;

	cmd_path = find_command(argv[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, argv, environ) == -1)
			perror("Error");
		exit(1);
	}
	else
	{
		wait(NULL);
	}

	free(cmd_path);
}
