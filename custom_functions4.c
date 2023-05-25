#include "main.h"

/**
 * free_args - Free the memory allocted for arguments
 * @argv: The array to free
 */
void free_args(char **argv)
{
	int i;

	if (argv == NULL)
		return;

	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
}

/**
 * find_command - Find full path of a command in a path
 * @command: the command to search for
 * @path: the value of the path
 *
 * Return: if found, the full path of the command or NULL
 */
char *find_command(const char *command, const char *path)
{
	char *full_command = NULL;
	char *dir = _strtok(_strdup(path), ":");
	char *temp;

	while (dir != NULL)
	{
		temp = malloc(_strlen(dir) + _strlen(command) + 2);
		_strcpy(temp, dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (access(temp, F_OK) == 0)
		{
			full_command = temp;
			break;
		}

		free(temp);
		dir = _strtok(NULL, ":");
	}

	return (full_command);
}

/**
 * _strncmp - compares characters of two strings
 * @s1: the first string to compare
 * @s2: the second string to comapre
 * @n: the max number of characters to comapre
 *
 * Return: diff between the two string
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (0);
}

/**
 * _getenv - searches for environmental var name
 * @name: he variable to search for
 *
 * Return: The value of the env. variable or NULL if not found
 */
char *_getenv(const char *name)
{
	size_t name_len = _strlen(name);
	size_t i;

	if (name == NULL || environ == NULL)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
	}

	return (NULL);
}

/**
 * _putserror - Prints error message to standard error stream
 * @err: The error to print
 */
void _putserror(const char *err)
{
	size_t len;
	ssize_t num_written;

	len = _strlen(err);
	num_written = write(STDERR_FILENO, err, len);
	if (num_written == -1)
	{
		perror("write");
	}
}
