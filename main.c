#include "shell.h"

int last_status = 0;

/**
 * main - simple shell
 * Return: exit status
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *token;
	char *args[100];
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (read > 1 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		i = 0;
		token = strtok(line, " \t");
		while (token && i < 99)
		{
			args[i++] = token;
			token = strtok(NULL, " \t");
		}
		args[i] = NULL;

		if (args[0])
			execute_command(args);
	}

	free(line);
	return (last_status);
}
