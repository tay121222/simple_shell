#include "shell.h"

/**
 * mk_env - create a shell environment using the environment passed to main
 * @env: the environment to be passed to the main function
 *
 * Return: new envoronment's pointer
 */
char **mk_env(char **env)
{
	char **nEnv = NULL;
	size_t a;

	for (a = 0; env[a] != NULL; a += 1)
		;
	nEnv = malloc(sizeof(char *) * (a + 1));
	if (nEnv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (a = 0; env[a] != NULL; a += 1)
		nEnv[a] = _strdup(env[a]);
	nEnv[a] = NULL;
	return (nEnv);
}

/**
 * fr_env - clear/free the shell environment
 * @env: environment for the shell
 *
 * Return: nothing
 */
void fr_env(char **env)
{
	unsigned int a;

	for (a = 0; env[a] != NULL; a += 1)
		free(env[a]);
	free(env);
}