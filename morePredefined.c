#include "shell.h"

/**
 * add_key - make new env variable
 * @vars: struct variable pointer
 *
 * Return: nothing
 */
void add_key(vars_t *vars)
{
	unsigned int a;
	char **newenv;

	for (a = 0; vars->env[a] != NULL; a += 1)
		;
	newenv = malloc(sizeof(char *) * (a + 2));
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (a = 0; vars->env[a] != NULL; a += 1)
		newenv[a] = vars->env[a];
	newenv[a] = add_value(vars->av[1], vars->av[2]);
	if (newenv[a] == NULL)
	{
		print_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		free_env(vars->env);
		free(newenv);
		exit(127);
	}
	newenv[a + 1] = NULL;
	free(vars->env);
	vars->env = newenv;
}

/**
 * find_key - finds environment variables
 * @env: array of environment variables
 * @key: env vars being searched for.
 *
 * Return: address pointer of environment variable
 */
char **find_key(char **env, char *key)
{
	unsigned int a, b, len;

	len = _strlen(key);
	for (a = 0; env[a] != NULL; a += 1)
	{
		for (b = 0; b < len; b += 1)
			if (key[b] != env[a][b])
				break;
		if (b == len && env[a][b] == '=')
			return (&env[a]);
	}
	return (NULL);
}

/**
 * add_value - make new env string variable
 * @key: name of variable
 * @value: value in variable
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int length1, length2, a, b;
	char *new;

	length1 = _strlen(key);
	length2 = _strlen(value);
	new = malloc(sizeof(char) * (length1 + length2 + 2));
	if (new == NULL)
		return (NULL);
	for (a = 0; key[a] != '\0'; a += 1)
		new[a] = key[a];
	new[a] = '=';
	for (b = 0; value[b] != '\0'; b += 1)
		new[a + 1 + b] = value[b];
	new[a + 1 + b] = '\0';
	return (new);
}

/**
 * _atoi - function in the C programming language that
 * converts a string into an integer
 * @str: string to be converted
 *
 * Return: an integer if successful/ -1 if failed
 */
int _atoi(char *str)
{
	unsigned int a, dgts;
	int number = 0, numberT;

	numberT = INT_MAX;
	for (dgts = 0; numberT != 0; dgts++)
		numberT /= 10;
	for (a = 0; str[a] != '\0' && a < dgts; a += 1)
	{
		number *= 10;
		if (str[a] < '0' || str[a] > '9')
			return (-1);
		if ((a == dgts - 1) && (str[a] - '0' > INT_MAX % 10))
			return (-1);
		number += str[a] - '0';
		if ((a == dgts - 2) && (str[a + 1] != '\0') && (number > INT_MAX / 10))
			return (-1);
	}
	if (a > dgts)
		return (-1);
	return (number);
}
