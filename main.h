#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024
#define MAX_ARGS 64
#define TOKEN_DELIM " \t\r\n\a"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

extern char **environ;
extern char *__progname;
char *program_name;

void execute_command(char **tokens);
size_t _strlen(const char *str);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
void _puts(char *str);
void _putserror(const char *err);
char *_strpbrk(const char *str, const char *accept);
size_t _strspn(const char *str, const char *accept);
char *_strchr(const char *str, int c);
char *_strtok(char *str, const char *delim);
void free_args(char **argv);
void parse_command(char *command, char **argv);
char *find_command(const char *command, const char *path);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcat(char *dest, const char *src);
char *_getenv(const char *name);
char *find_path(const char *command);
void _puts(char *str);
char **parse_input2(char *input);
char *find_path(const char *command);
char **tokenize(const char *str, const char *delimiters);
int is_path(const char *command);
int _strcmp(const char *s1, const char *s2);
int is_env(const char *command);
void execute_env(void);
void execute_child(char **tokens, char *command);
void execute_parent(char **tokens, pid_t pid, int *status, char **full_path);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_memcpy(void *dest, const void *src, size_t n);
void tokenization_error(char **tokens, char *str_copy, int token_count);
void free_last_input(char **last_input);
char *store_last_input(const char *input, ssize_t size);
char *_strncpy(char *dest, const char *src, size_t n);

#endif
