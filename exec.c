#include "shell.h"

/**
 * find_command - finds the full path of a command
 * @command: command name
 * Return: full path or NULL
 */
char *find_command(char *command)
{
	char *path;
	char *path_copy;
	char *dir;
	char full_path[1024];

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
