#include "shell.h"
/**
 * checkPredefineds - check if command is a built-in command
 * @vars: programme variables
 * Return: NULL/ Function pointer.
 */
void (*checkPredefineds(vars_t *vars))(vars_t *vars)
{
	unsigned int a;
	predefined_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (a = 0; check[a].f != NULL; a += 1)
	{
		if (_strcmpr(vars->av[0], check[a].name) == 0)
			break;
	}
	if (check[a].f != NULL)
		check[a].f(vars);
	return (check[a].f);
}

/**
 * new_exit - exit from the program
 * @vars: the variables
 * Return: mothing
 */
void new_exit(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}

/**
 * _env - prints the current environment
 * @vars: variable struct
 * Return: void.
 */
void _env(vars_t *vars)
{
	unsigned int a;

	for (a = 0; vars->env[a]; a += 1)
	{
		_puts(vars->env[a]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * new_setenv - Creates new or edit an existing variable
 * @vars: pointer for variable struct
 *
 * Return: nothing
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * new_unsetenv - delete environment variable
 * @vars: pointer for variable struct
 *
 * Return: nothing
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;

	unsigned int a, b;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset");
		return;
	}
	for (a = 0; vars->env[a] != NULL; a += 1)
		;
	newenv = malloc(sizeof(char *) * a);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (a = 0; vars->env[a] != *key; a += 1)
		newenv[a] = vars->env[a];
	for (b = a + 1; vars->env[b] != NULL; b += 1, a += 1)
		newenv[a] = vars->env[b];
	newenv[a] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}
