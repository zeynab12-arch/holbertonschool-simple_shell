#include "shell.h"

/**
 * find_path - finds PATH value from environ
 * Return: pointer to PATH string or NULL
 */
char *find_path(void)
{
	int i = 0;
	char *path = NULL;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5; /* skip "PATH=" */
			break;
		}
		i++;
	}
	return (path);
}

/**
 * find_command - finds full path of command in PATH
 * @command: command name
 * Return: full path string or NULL
 */
char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	char full_path[1024];

	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = find_path();
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
