#include "shell.h"


/**
 * tokenize - uses delimiter to tokenizes a buffer
 * @buffer: the buffer to be tokenize
 * @delimiter: the delimiter.
 *
 * Return: points to array of pointers for the tokens
 */
char **tokenize(char *buffer, char *delimiter)
{
	char **tokens = NULL;
	size_t a = 0, m_count = 10;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * m_count);
	if (tokens == NULL)
	{
		perror("deadly Error");
		return (NULL);
	}
	while ((tokens[a] = new_strtok(buffer, delimiter)) != NULL)
	{
		a += 1;
		if (a == m_count)
		{
			tokens = _realloc(tokens, &m_count);
			if (tokens == NULL)
			{
				perror("deadly Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
