#include "shell.h"

/**
* main - Main loop that parses input from Command Line interface and executes
* @argc: Number of args passed to the program
* @argv: Array of arguments
* Return: Always 0 on success
*/

int main(int argc __attribute__((unused)),
		char *argv[] __attribute__((unused)))
{
	char **args = NULL;
	char *input_stdin = NULL;
	int status_return = 1, exit_status = 0;
	size_t size = 0;
	ssize_t glrv = 0;

	while (status_return && glrv != EOF)
	{
		size = 0;
		status_return = isatty(STDIN_FILENO);
		if (status_return)
			write(STDOUT_FILENO, "$ ", 2);
		glrv = getline(&input_stdin, &size, stdin);
		if (glrv == -1)
		{
			free(input_stdin);
			break;
		}
		if (validate_only_spaces(input_stdin))
		{
			free(input_stdin);
			continue;
		}
		args = hsh_tokenizer(input_stdin);
		if (*args[0] == '\0')
			continue;
		status_return = hsh_execute_builtins(args, input_stdin,
		argv, &exit_status);
		free(input_stdin);
		free(args);
	}
	return (0);
}
