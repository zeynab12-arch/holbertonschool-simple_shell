#include "shell.h"

/**
 * main - simple shell
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t size = 0;
	char *args[64];
	char *token;
	int i;

	while (1)
	{
		printf(":) ");
		fflush(stdout);

		if (getline(&line, &size, stdin) == -1)
		{
			printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (line[0] == '\0')
			continue;

		i = 0;
		token = strtok(line, " ");

		while (token != NULL && i < 63)
		{
			args[i] = token;
			i++;
			token = strtok(NULL, " ");
		}

		args[i] = NULL;

		if (args[0] != NULL)
			execute_command(args);
	}

	free(line);
	return (0);
}
