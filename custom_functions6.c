#include "main.h"

/**
 * free_last_input - frees last input made by user
 * @last_input: the input to free
 */
void free_last_input(char **last_input)
{
	if (*last_input != NULL)
	{
		free(*last_input);
		*last_input = NULL;
	}
}

/**
 * store_last_input - Stores last input made by user
 * @input: the input made by user
 * @size: size of input
 *
 * Return: last input
 */
char *store_last_input(const char *input, ssize_t size)
{
	char *last_input = malloc((size + 1) * sizeof(char));

	if (last_input == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	_strncpy(last_input, input, size);
	last_input[size] = '\0';
	return (last_input);
}

/**
 * strncpy - cpies string from one location to another
 * @dest: points to the destination string
 * @src: points to the source string
 * @n: number of characters to copy
 *
 * Return: Pointer to destination
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

