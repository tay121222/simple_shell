#include "shell.h"

/**
 * print_error - print error messages
 * @vars: struct variables pointer
 * @mssg: message to print
 *
 * Return: nothing
 */
void print_error(vars_t *vars, char *mssg)
{
	char *counter;

	_puts2(vars->argv[0]);
	_puts2(": ");
	counter = _uitoa(vars->counter);
	_puts2(counter);
	free(counter);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (mssg)
	{
		_puts2(mssg);
	}
	else
		perror("");
}

/**
 * _puts2 - prints a string
 * @str: string to print
 *
 * Return: nothing
 */
void _puts2(char *str)
{
	ssize_t numb, length;

	numb = _strlen(str);
	length = write(STDERR_FILENO, str, numb);
	if (length != numb)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - converts integer to a string
 * @counter: inter to be convert
 *
 * Return: a pointer for converted string
 */
char *_uitoa(unsigned int counter)
{
	char *numstr;
	unsigned int temp, dgts;

	temp = counter;
	for (dgts = 0; temp != 0; dgts += 1)
		temp /= 10;
	numstr = malloc(sizeof(char) * (dgts + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[dgts] = '\0';
	for (--dgts; counter; --dgts)
	{
		numstr[dgts] = (counter % 10) + '0';
		counter /= 10;
	}
	return (numstr);
}
