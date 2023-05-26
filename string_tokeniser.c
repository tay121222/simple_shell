#include "shell.h"

/**
 * check_match - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if is_match/ 0 if no_match
 */
unsigned int check_match(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * new_strtok - custom string token
 * @str: string to be tokenised
 * @delimitr: delimiter to tokenise
 *
 * Return: NULL/ ptr to next token.
 */
char *new_strtok(char *str, const char *delimitr)
{
	static char *token_strt;
	static char *nxt_token;
	unsigned int a;

	if (str != NULL)
		nxt_token = str;
	token_strt = nxt_token;
	if (token_strt == NULL)
		return (NULL);
	for (a = 0; nxt_token[a] != '\0'; a += 1)
	{
		if (check_match(nxt_token[a], delimitr) == 0)
			break;
	}
	if (nxt_token[a] == '\0' || nxt_token[a] == '#')
	{
		nxt_token = NULL;
		return (NULL);
	}
	token_strt = nxt_token + a;
	nxt_token = token_strt;
	for (a = 0; nxt_token[a] != '\0'; a += 1)
	{
		if (check_match(nxt_token[a], delimitr) == 1)
			break;
	}
	if (nxt_token[a] == '\0')
		nxt_token = NULL;
	else
	{
		nxt_token[a] = '\0';
		nxt_token = nxt_token + a + 1;
		if (*nxt_token == '\0')
			nxt_token = NULL;
	}
	return (token_strt);
}
