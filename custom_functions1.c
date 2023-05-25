#include "main.h"

/**
 * _strcmp - compare two string
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if string is equal or otherwise
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * is_env - Checks if a given coomand in an environ. vaariable
 * @command: the command to check
 *
 * Return: 1 if true, 0 otherwise
 */
int is_env(const char *command)
{
	char **env = environ;

	while (*env != NULL)
	{
		char *env_var = *env;
		char *env_name = _strtok(env_var, "=");

		if (env_name != NULL && _strcmp(env_name, command) == 0)
			return (1);
		env++;
	}
	return (0);
}

/**
 * execute_env - Executes a command
 */
void execute_env(void)
{
	char **value = environ;

	while (*value != NULL)
	{
		_puts(*value);
		_puts("\n");
		value++;
	}
}

/**
 * tokenization_error - Handles memory deallocation
 * @tokens: the aray of tokens
 * @str_copy: The duplicated string to be freed
 * @token_count: the number of tokens created
 */
void tokenization_error(char **tokens, char *str_copy, int token_count)
{
	int i;

	for (i = 0; i < token_count; i++)
		free(tokens[i]);
	free(tokens);
	free(str_copy);
}
