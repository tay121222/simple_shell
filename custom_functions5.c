#include "main.h"
#include <sys/stat.h>
/**
 * find_path - finds path of command
 * @command: command to find path
 *
 * Return: Returns path if found or Null
 */
char *find_path(const char *command)
{
	char *path = _getenv("PATH");
	char *command_path = NULL;
	char *token;

	if (command[0] == '/')
	{
		if (access(command, F_OK) == 0)
			command_path = _strdup(command);
	}
	else
	{
		token = _strtok(path, ":");
		while (token != NULL)
		{
			size_t token_len = _strlen(token);
			size_t command_len = _strlen(command);
			char *temp_path = malloc(token_len + 1 + command_len + 1);

			if (!temp_path)
			{
				_putserror("malloc");
				exit(98);
			}
			_strcpy(temp_path, token);
			temp_path[token_len] = '/';
			_strcpy(temp_path + token_len + 1, command);

			if (access(temp_path, F_OK) == 0)
			{
				command_path = temp_path;
				break;
			}
			free(temp_path);
			token = _strtok(NULL, ":");
		}
	}
	return (command_path);
}

/**
 * parse_input2 - Tokenize the input string
 * @input: the input string to tokenize
 *
 * Return: An array of tokens
 */
char **parse_input2(char *input)
{
	char **tokens = NULL;
	char *tmp = NULL;

	tmp = _strdup(input);
	if (tmp == NULL)
	{
		_putserror("Memory allocation error\n");
		exit(98);
	}
	tokens = tokenize(tmp, TOKEN_DELIM);
	free(tmp);
	free_args(tokens);

	return (tokens);
}

/**
 * tokenize - split a string into tokens
 * @str: the string to split
 * @delimiters: the delimiters to use for the split
 *
 * Return: array of strings containg the tokens
 */
char **tokenize(const char *str, const char *delimiters)
{
	char **tokens, *token, *str_copy;
	int token_count;

	if (!str || !delimiters)
		return (NULL);

	tokens = malloc(MAX_ARGS * sizeof(char *));
	if (!tokens)
		return (NULL);
	token_count = 0;
	str_copy = _strdup(str);

	if (!str_copy)
	{
		tokenization_error(tokens, str_copy, token_count);
		return (NULL);
	}

	token = _strtok(str_copy, delimiters);
	while (token != NULL && token_count < MAX_ARGS - 1)
	{
		tokens[token_count] = _strdup(token);
		if (!tokens[token_count])
		{
			tokenization_error(tokens, str_copy, token_count);
			return (NULL);
		}
		token_count++;
		token = _strtok(NULL, delimiters);
	}
	if (token == NULL && token_count == MAX_ARGS - 1)
	{
		tokenization_error(tokens, str_copy, token_count);
		return (NULL);
	}

	tokens[token_count] = NULL;
	free(str_copy);
	return (tokens);
}

/**
 * _puts - Prints a string to the standard output stream
 * @str: The string to print
 */
void _puts(char *str)
{
	size_t len;
	ssize_t num_written;

	len = _strlen(str);
	num_written = write(STDOUT_FILENO, str, len);
	if (num_written == -1)
	{
		perror("write");
		exit(98);
	}
}

/**
 * is_path - checks if command is absolute or relative path
 * @command: The command to check
 *
 * Return: 1 if absolute or relative path or 0 otherwise
 */
int is_path(const char *command)
{
	if (command[0] == '/')
		return (1);
	if (command[0] == '.' && command[1] == '/')
		return (1);
	return (0);
}
