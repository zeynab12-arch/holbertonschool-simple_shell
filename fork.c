void execute_command(char **args)
{
	pid_t pid;
	char *cmd_path;

	if (!args[0])
		return;

	cmd_path = find_command(args[0]);

	if (!cmd_path)
	{
		perror("./shell");
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}

	free(cmd_path);
}
