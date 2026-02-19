if (args[0])
{
    if (strcmp(args[0], "exit") == 0)
        break;

    if (strcmp(args[0], "env") == 0)
    {
        int j = 0;
        while (environ[j])
        {
            write(STDOUT_FILENO, environ[j], strlen(environ[j]));
            write(STDOUT_FILENO, "\n", 1);
            j++;
        }
        continue;
    }

    execute_command(args);
}
