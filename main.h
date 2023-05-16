#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_command(const char *command);
size_t _strlen(const char *str);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);

#endif
