#include "main.h"

/**
 * execute_child - execute child process
 * @tokens: the array of command token
 * @command: the command to execute
 */
void execute_child(char **tokens, char *command)
{
	if (is_path(command))
	{
		if (execve(command, tokens, NULL) == -1)
		{
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		char *full_path = find_path(command);

		if (full_path == NULL)
		{
			_puts(program_name);
			_puts(": command not found\n");
			free_args(tokens);
			exit(EXIT_FAILURE);
		}
		if (execve(full_path, tokens, NULL) == -1)
		{
			perror(program_name);
			free_args(tokens);
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * execute_parent - Executes the command in main process
 * @tokens: the array of commands
 * @pid: the child process id
 * @status: Pointer to the status variable for waitpid
 * @full_path: pointer to full path
 */
void execute_parent(char **tokens, pid_t pid, int *status, char **full_path)
{
	if (waitpid(pid, status, 0) == -1)
	{
		perror("waitpid");
		free_args(tokens);
		exit(EXIT_FAILURE);
	}
	if (*full_path != NULL)
	{
		free(*full_path);
		free_args(tokens);
	}
}

/**
 * _realloc - rellocates a bloc of memory
 * @ptr: pointer to previous allocated block
 * @old_size: byte size of prev. block
 * @new_size: byte size of new block
 *
 * Return: pointer to reallocated mem.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	mem = malloc(new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size < old_size)
		old_size = new_size;

	_memcpy(mem, ptr, old_size);
	free(ptr);

	return (mem);
}

/**
 * _memcpy - copies memory area
 * @dest: area to copy to
 * @src: where to copy from
 * @n: bytes of src
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = dest;
	const unsigned char *s = src;

	while (n--)
		*d++ = *s++;
	return (dest);
}
