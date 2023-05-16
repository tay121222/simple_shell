#include "main.h"

/**
 * main - Entry Point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	const char *prompt = "#cisfun$ ";
	char buffer[BUFFER_SIZE];
	ssize_t read_size;

	while (1)
	{
		ssize_t write_size = write(STDOUT_FILENO, prompt, _strlen(prompt));

		if (write_size == -1)
		{
			perror("write");
			exit(98);
		}
		read_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (read_size < 0)
		{
			perror("read");
			exit(98);
		}
		if (read_size == 0)
		{
			if (isatty(STDIN_FILENO))
			{
				ssize_t line_size = write(STDOUT_FILENO, "\n", 1);

				if (line_size == -1)
				{
					perror("write");
					exit(98);
				}
			}
			break;
		}

		buffer[read_size - 1] = '\0';

		execute_command(buffer);
	}

	return (0);
}
