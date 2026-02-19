#include "shell.h"

#define BUFFER_SIZE 1024

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
			printf("$ ");

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		i = 0;
		token = strtok(line, " ");
		while (token && i < 99)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		execute_command(args);
	}

	free(line);
	return (0);
}
