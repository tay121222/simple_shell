#include "main.h"

/**
 * print_prompt - Print the shell prompt
 * @prompt: the prompt string to print
 */
void print_prompt(const char *prompt)
{
	ssize_t write_size = write(STDOUT_FILENO, prompt, _strlen(prompt));

	if (write_size == -1)
	{
		perror("write");
		exit(98);
	}
}

/**
 * read_input - Read user input from stdin
 * @buffer: the buffer to store the input
 *
 * Return: The number of bytes read
 */
ssize_t read_input(char *buffer)
{
	ssize_t read_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);

	if (read_size < 0)
	{
		perror("read");
		exit(98);
	}
	return (read_size);
}

/**
 * empty_input - Handle empty inputs
 */
void empty_input(void)
{
	if (isatty(STDIN_FILENO))
	{
		ssize_t line_size = write(STDOUT_FILENO, "\n", 1);

		if (line_size == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * main - Entry Point of the program
 * @argc: number of arguments
 * @argv: pointer to array of arguments
 *
 * Return: Always 0 (Success)
 */
int main(__attribute__((unused))int argc, char *argv[])
{
	const char *prompt = "#cisfun$ ";
	char buffer[BUFFER_SIZE];
	ssize_t read_size;
	char **tokens;

	program_name = argv[0];
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			print_prompt(prompt);
		}
		read_size = read_input(buffer);

		if (read_size < 0)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		if (read_size == 1)
			continue;

		if (read_size == 0)
		{
			empty_input();
			break;
		}
		buffer[read_size - 1] = '\0';
		/* tokens = parse_input2(buffer); */
		tokens = tokenize(buffer, TOKEN_DELIM);
		if (_strcmp(buffer, "env") == 0)
		{
			execute_env();
			free_args(tokens);
			continue;
		}
		execute_command(tokens);
		free_args(tokens);
	}
	return (EXIT_SUCCESS);
}
