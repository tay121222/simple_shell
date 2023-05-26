#include "shell.h"
/**
 * reAlloc - creates more space by reallocating pointer
 * @pointer: points to initial array
 * @sze: points to no. of elements in previous array
 *
 * Return: pointer to the new array
 */
char **reAlloc(char **pointer, size_t *sze)
{
	char **new;
	size_t q;

	new = malloc(szeof(char *) * ((*sze) + 10));
	if (new == NULL)
	{
		free(pointer);
		return (NULL);
	}
	for (q = 0; q < (*sze); q += 1)
	{
		new[q] = pointer[q];
	}
	*sze += 10;
	free(pointer);
	return (new);
}
