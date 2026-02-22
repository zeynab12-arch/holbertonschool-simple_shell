#include "shell.h"

char **split_line(char *line)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = malloc(sizeof(char *) * 64);
	if (!tokens)
		return (NULL);

	token = strtok(line, " ");
	while (token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;

	return (tokens);
}

void free_args(char **args)
{
	free(args);
}
