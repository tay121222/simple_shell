#include "main.h"

/**
 * _strcpy - copy string form source to destination
 * @dest: destination string
 *
 * @src: the source string
 *
 * Return: Pointer to the dest. string
 */
char *_strcpy(char *dest, const char *src)
{
	char *ptr = dest;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (ptr);
}

/**
 * _strdup - functions duplicates string
 * @str: string to duplicate
 *
 * Return: Pointer to the newly allocated duplicated string
 */
char *_strdup(const char *str)
{
	char *dup;
	size_t len, i;

	if (str == NULL)
		return (NULL);

	len = 0;
	while (str[len])
		len++;

	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup[i] = str[i];

	return (dup);
}
/**
 * _strlen - Functions measures the length of string
 * @str: the string to measure length
 *
 * Return: The length pf the string
 */
size_t _strlen(const char *str)
{
	size_t len = 0;
	const char *s = str;

	while (*s != '\0')
	{
		len++;
		s++;
	}

	return (len);
}

/**
 * _strcat - function concatenate string
 * @dest: the destination string
 * @src: the sorce string
 *
 * Return: Pointer to the dest string
 */
char *_strcat(char *dest, const char *src)
{
	char *temp = dest;

	while (*temp)
		temp++;

	while (*src)
		*temp++ = *src++;

	*temp = '\0';

	return (dest);
}
/**
 * execute_command - Execute a command
 * @tokens: tokenized user inputs
 */
void execute_command(char **tokens)
{
	char *full_path = NULL;
	pid_t pid;
	int status;
	char *command = tokens[0];

	if (_strcmp(command, "exit") == 0)
	{
		free_args(tokens);
		exit(98);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error Child:");
		exit(98);
	}
	else if (pid == 0)
	{
		execute_child(tokens, command);
	}
	else
	{
		execute_parent(tokens, pid, &status, &full_path);
	}
}
