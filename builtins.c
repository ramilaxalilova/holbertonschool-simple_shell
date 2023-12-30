#include "shell.h"

/**
 * hsh_cd - Change directory
 *
 * @args: Array of tokens
 * @input_stdin: Input from stdin
 * @exit_status: Exit status
 *
 * Return: Always 1 (success)
 */
int hsh_cd(char **args, char *input_stdin, int *exit_status)
{
	int status;
	char cwd[128];

	getcwd(cwd, sizeof(cwd));

	(void)input_stdin;
	(void)exit_status;

	if (args[1] == NULL)
		status = chdir(getenv("HOME"));
	else if (strcmp(args[1], "-") == 0)
		status = chdir(getenv("OLDPWD"));
	else if (strcmp(args[1], "~") == 0)
		status = chdir(getenv("HOME"));
	else
		status = chdir(args[1]);

	if (status == -1)
		perror("cd: error");

	setenv("OLDPWD", cwd, 1);

	setenv("PWD", getcwd(cwd, sizeof(cwd)), 1);
	return (1);
}

/**
 * hsh_setenv - Adds or changes an environment variable
 *
 * @args: Array of tokens from input
 * @input_stdin: Input from stdin
 * @exit_status: Exit status
 *
 * Return: Always 1 (success)
 */
int hsh_setenv(char **args,  char *input_stdin, int *exit_status)
{
	int n_tokens = 0;

	(void)input_stdin;
	(void)exit_status;

	while (args[n_tokens] != NULL)
	{
		n_tokens++;
	}

	if (n_tokens == 3)
		setenv(args[1], args[2], 1);

	else
		fprintf(stderr, "incorrect format, use: \"setenv [KEY] [VALUE]\"\n");

	return (1);
}

/**
 * hsh_unsetenv - Deletes an env var from the environment
 *
 * @args: Array of tokens from input
 * @input_stdin: Input from stdin
 * @exit_status: Exit status
 *
 * Return: Always 1 (success)
 */
int hsh_unsetenv(char **args,  char *input_stdin, int *exit_status)
{
	int n_tokens = 0;

	(void)input_stdin;
	(void)exit_status;

	while (args[n_tokens] != NULL)
	{
		n_tokens++;
	}

	if (n_tokens == 2)
		unsetenv(args[1]);
	else if (n_tokens != 2)
		fprintf(stderr, "incorrect format, use: \"unsetenv [KEY]\"\n");

	return (1);
}

/**
 * hsh_env - Prints enviroment variable of current process
 *
 * @args: arguments
 * @input_stdin: input of stdin
 * @exit_status: exit status
 *
 * Return: Always 1 (success)
 */
int hsh_env(char **args, char *input_stdin, int *exit_status)
{
	int i = 0;

	(void)args;
	(void)input_stdin;
	(void)exit_status;

	if (environ[i] == NULL)
	{
		printf("%s\n", "The builtin env is empty");
		return (1);
	}

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);

	return (1);
}

/**
 * hsh_exit - Function exits the shell
 *
 * @args: arguments
 * @input_stdin: input of stdin
 * @exit_status: exit status
 *
 * Return: 0 on failure otherwise exits and returns
 * the exit status
 */
int hsh_exit(char **args, char *input_stdin, int *exit_status)
{
	int output_exit = 0;

	(void)args;
	(void)input_stdin;

	if (args[1] == NULL)
	{
		free(args);
		free(input_stdin);
		exit(*exit_status);
	}

	if (args[2] != NULL)
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (0);
	}

	output_exit = atoi(args[1]);
	free(args);
	free(input_stdin);
	exit(output_exit);
}
