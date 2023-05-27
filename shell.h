#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: counts of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} vars_t;

/**
 * struct predefined - struct for the builtin functions
 * @name: name of built-in command
 * @f: function for corresponding built-in
 */
typedef struct predefined
{
	char *name;
	void (*f)(vars_t *);
} predefined_t;

char **mk_env(char **env);
void fr_env(char **env);

ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

char **tokenize(char *buffer, char *delimiter);
char **reAlloc(char **pointer, size_t *sze);
char *new_strtok(char *str, const char *delimitr);

void (*checkPredefineds(vars_t *vars))(vars_t *vars);
void n_exit(vars_t *vars);
void _env(vars_t *vars);
void new_setenv(vars_t *vars);
void new_unsetenv(vars_t *vars);

void add_key(vars_t *vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);

void chk_path(vars_t *vars);
int path_exec(char *cmd, vars_t *vars);
char *f_path(char **env);
int exec_cwd(vars_t *vars);
int chk_dir(char *str);

void print_error(vars_t *vars, char *msg);
void _puts2(char *str);
char *_uitoa(unsigned int counter);

#endif /* _SHELL_H_ */
