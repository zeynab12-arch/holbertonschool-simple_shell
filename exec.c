#include "shell.h"

/**
 * find_command - finds the full path of a command in PATH
 * @command: command name
 * Return: full path string if exists, else NULL
 */
char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	char full_path[1024];

	/* If command contains /, check directly */
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
	if (!path_copy)
		return (NULL);

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
