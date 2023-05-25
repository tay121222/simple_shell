#include "main.h"

/**
 * _strpbrk - searches a string for first occurence of a character
 * @str: the string to search
 * @accept: the character to search for
 *
 * Return: A pointer to the first occurrence of char or Null
 */
char *_strpbrk(const char *str, const char *accept)
{
	const char *s = str;
	const char *a;

	while (*s != '\0')
	{
		a = accept;

		while (*a != '\0')
		{
			if (*s == *a)
				return ((char *)s);
			a++;
		}
		s++;
	}

	return (NULL);
}

/**
 * _strspn - calculate lenght of string found in another string
 * @str: the string to search in
 * @accept: the characters to search for
 *
 * Return: The length of str that exist in accept
 */
size_t _strspn(const char *str, const char *accept)
{
	size_t count = 0;

	while (*str && _strchr(accept, *str++))
		count++;

	return (count);
}

/**
 * _strchr - Find the first occurence of a character in a string
 * @str: the string to search in
 * @c: the character to search for
 *
 * Return: A pointer to first occurence of the character found
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}

	if (c == '\0')
		return ((char *)str);

	return (NULL);
}

/**
 * _strtok - split string based on delimiter
 * @str: the string to split
 * @delim: the delimiter
 *
 * Return: pointer to the next splited string or NULL
 */
char *_strtok(char *str, const char *delim)
{
	static char *next_token;
	 char *token_start, *token_end;

	if (str != NULL)
		next_token = str;

	if (next_token == NULL || *next_token == '\0')
		return (NULL);

	token_start = next_token;
	token_end = _strpbrk(next_token, delim);

	if (token_end != NULL)
	{
		*token_end = '\0';
		next_token = token_end + 1;
	}
	else
	{
		next_token = NULL;
	}

	return (token_start);
}

/**
 * parse_command - parse command into arguments
 * @command: the command to parse
 * @argv: The array to store the parsed arguments
 */
void parse_command(char *command, char **argv)
{
	int argc = 0;
	char *token;
	char *buffer = _strdup(command);

	token = _strtok(buffer, " \t\r\n\a");
	while (token != NULL && argc < MAX_ARGS - 1)
	{
		argv[argc] = _strdup(token);
		token = _strtok(NULL, " \t\r\n\a");
		argc++;
	}

	argv[argc] = NULL;
	free(buffer);
}
