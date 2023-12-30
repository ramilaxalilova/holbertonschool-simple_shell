#include "shell.h"

/**
* validate_input - Validates if the PATH exists
* @args: String of Tokens
* @argv: String of arguments from input
* Return: A pointer to an array of the tokenized PATH directories
*/
char *validate_input(char **args, char **argv) /* */
{
	char *new_args, *first, *slash_argument = "/";
	char **tokens_path, holder_env[1024];
	int i = 0;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		new_args = args[0];

		if ((access(new_args, F_OK) == -1))
		{
			fprintf(stderr, "%s: %d: %s: No such file or directory\n",
			argv[0], __LINE__, args[0]);

			return ("Fail access");
		}
	}
	else
	{
		strcpy(holder_env, getenv("PATH"));

		tokens_path = tokenizer_path(holder_env);
		while (tokens_path[i])
		{
			first = str_concat(slash_argument, args[0]);
			new_args = str_concat(tokens_path[i], first);
			if ((access(new_args, F_OK) == -1))
			{
				free(new_args);
				free(first);
			}
			else
			{
				free(tokens_path);
				free(first);
				return (new_args);
			}
			i++;
		}
		free(tokens_path);
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
		argv[0], __LINE__, args[0]);

		return ("Fail access");
	}
	return (new_args);
}

/**
* validate_only_spaces - Checks if input is only spaces
* @input: string from input
* Return: 0 if there are spaces, tabs or line breaks
*/
int validate_only_spaces(char *input)
{
	int i = 0, flag = 1, len = 0;

	len = strlen(input);

	while (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
		i++;

	if (i != len)
		flag = 0;
	return (flag);
}
