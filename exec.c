#include "shell.h"

/**
 * find_command - finds command in PATH
 * @command: command name
 * Return: full path or NULL
 */
char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	char full_path[1024];
	struct stat st;

	/* If command contains / */
	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
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
