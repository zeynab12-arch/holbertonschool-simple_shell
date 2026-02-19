# Simple Shell

## Description

`simple_shell` is a simple Unix command-line interpreter written in C.  
It can execute commands, handle PATH, implement built-in commands (`exit`, `env`), and manage child processes with `fork` and `execve`.

## Features

- Execute binary commands like `/bin/ls`, `ls -l`, etc.
- Handles the `PATH` environment variable manually.
- Implements built-in commands:
  - `exit` → exits the shell
  - `env` → prints the current environment
- Prevents `fork` if command does not exist.
- Compatible with interactive and non-interactive modes.

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
