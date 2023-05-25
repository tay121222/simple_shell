#include "main.h"

/**
 * main - Entry Point of the program
 * @argc: the number of arguments
 * @argv: array of pointers to the arguments
 *
 * Return: Always 0 (Success)
 */
int main(__attribute__((unused))int argc, char *argv[])
{
	const char *prompt = "#cisfun$ ";
	char buffer[BUFFER_SIZE];
	ssize_t read_size;

	program_name = argv[0];
	while (1)
	{
		ssize_t write_size = write(STDOUT_FILENO, prompt, _strlen(prompt));

		if (write_size == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		read_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (read_size < 0)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		if (read_size == 0)
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
			break;
		}
		buffer[read_size - 1] = '\0';
		execute_command(buffer);
	}
	return (0);
}
