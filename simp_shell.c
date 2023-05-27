#include "shell.h"

/**
 * sig_handler - handles ^C signal interupt
 * @u_uv: unused variable (required for signal function prototype)
 *
 * Return: void
 */
static void sig_handler(int u_uv)
{
	unsigned int sig_flag = 0;
	(void) u_uv;

	if (sig_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * main - main function
 * @argc: no. of args passed to main function
 * @argv: array of args passed to main function
 * @environment: array containing enviro variables
 *
 * Return: exit status/ 0/ ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, a;

	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = mk_env(environment);
	signal(SIGINT, sig_handler);

	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");

	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		vars.count += 1;
		vars.commands = tokenize(vars.buffer, ";");
		for (a = 0; vars.commands && vars.commands[a] != NULL; a += 1)
		{
			vars.av = tokenize(vars.commands[a], "\n \t\r");
			if (vars.av && vars.av[0])
				if (checkPredefineds(&vars) == NULL)
					chk_path(&vars);
			free(vars.av);
		}
		free(vars.buffer);
		free(vars.commands);
		if (is_pipe == 0)
			_puts("$ ");
		vars.buffer = NULL;
	}
	if (is_pipe == 0)
		_puts("\n");
	fr_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
