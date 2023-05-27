#include "shell.h"
/**
 * path_exec - carries out command on path
 * @command: absolute path to command
 * @vars: pointer to struct of variables
 *
 * Return: zero if succcessful/ one if failed
 */
int path_exec(char *command, vars_t *vars)
{
	pid_t child_pd;

	if (access(command, X_OK) == 0)
	{
		child_pd = fork();
		if (child_pd == -1)
			print_error(vars, NULL);
		if (child_pd == 0)
		{
			if (execve(command, vars->av, vars->env) == -1)
				print_error(vars, NULL);
		}
		else
		{
			wait(&vars->status);
			if (WIFEXITED(vars->status))
				vars->status = WEXITSTATUS(vars->status);
			else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
				vars->status = 130;
			return (0);
		}
		vars->status = 127;
		return (1);
	}
	else
	{
		print_error(vars, ": Denied Permission\n");
		vars->status = 126;
	}
	return (0);
}
/**
 * f_path - searches for the path's variable
 * @env: environment variable array
 *
 * Return: NULL if failed/ node pointer for path
 */
char *f_path(char **env)
{
	char *path = "PATH=";
	unsigned int a, b;

	for (a = 0; env[a] != NULL; a += 1)
	{
		for (b = 0; b < 5; b++)
			if (path[b] != env[a][b])
				break;
		if (b == 5)
			break;
	}
	return (env[a]);
}
/**
 * chk_path - verifies if the command exists in PATH
 * @vars: the variables
 *
 * Return: nothing
 */
void chk_path(vars_t *vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int a = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	if (chk_dir(vars->av[0]))
		r = exec_cwd(vars);
	else
	{
		path = f_path(vars->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokenize(path_dup, ":");
			for (a = 0; path_tokens && path_tokens[a]; a += 1, free(check))
			{
				check = _strcat(path_tokens[a], vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					r = path_exec(check, vars);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				vars->status = 127;
				new_exit(vars);
			}
		}
		if (path == NULL || path_tokens[a] == NULL)
		{
			print_error(vars, ": not found\n");
			vars->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		new_exit(vars);
}
/**
 * exec_cwd - runs command in working directory
 * @vars: pointer for variable struct
 *
 * Return: 0 if successful/ 1 if failed
 */
int exec_cwd(vars_t *vars)
{
	pid_t child_pd;
	struct stat buf;

	if (stat(vars->av[0], &buf) == 0)
	{
		if (access(vars->av[0], X_OK) == 0)
		{
			child_pd = fork();
			if (child_pd == -1)
				print_error(vars, NULL);
			if (child_pd == 0)
			{
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					print_error(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			print_error(vars, ": Permission denied\n");
			vars->status = 126;
		}
		return (0);
	}
	print_error(vars, ": not found\n");
	vars->status = 127;
	return (0);
}
/**
 * chk_dir - verifies if command is part of path
 * @str: the command.
 *
 * Return: 1 if successful/ 0 if failed
 */
int chk_dir(char *str)
{
	unsigned int a;

	for (a = 0; str[a]; a += 1)
	{
		if (str[a] == '/')
			return (1);
	}
	return (0);
}
