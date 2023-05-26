#include "shell.h"

/**
 * _puts - prints string to standard output
 * @str: the string
 *
 * Return: no. of characters printed / -1 if failed
 */
ssize_t _puts(char *str)
{
	ssize_t number, length;

	number = _strlen(str);
	length = write(STDOUT_FILENO, str, number);
	if (length != number)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (length);
}

/**
 * _strdup - returns pointer to new mem alloc
 * @strtodup: strings to be duplicated
 * Return: pointer duplicated string
 */
char *_strdup(char *strtodup)
{
	char *copy;

	int length, a;

	if (strtodup == 0)
		return (NULL);

	for (length = 0; strtodup[length]; length += 1)
		;
	copy = malloc((length + 1) * sizeof(char));

	for (a = 0; a <= length; a += 1)
		copy[a] = strtodup[a];

	return (copy);
}

/**
 * _strcmpr - juxtaposes two strings
 * @strcmp1: string 1
 * @strcmp2: string 1
 * Return: 0 if successful/
 */
int _strcmpr(char *strcmp1, char *strcmp2)
{
	int a;

	a = 0;
	while (strcmp1[a] == strcmp2[a])
	{
		if (strcmp1[a] == '\0')
			return (0);
		a += 1;
	}
	return (strcmp1[a] - strcmp2[a]);
}

/**
 * _strcat - concatenates multiple strings
 * @strc1: string 1
 * @strc2: string 2
 * Return: a pointer
 */
char *_strcat(char *strc1, char *strc2)
{
	char *ntring;
	unsigned int length1, length2, newlen, a, b;

	length1 = 0;
	length2 = 0;
	if (strc1 == NULL)
		length1 = 0;
	else
	{
		for (length1 = 0; strc1[length1]; length1++)
			;
	}
	if (strc2 == NULL)
		length2 = 0;
	else
	{
		for (length2 = 0; strc2[length2]; length2++)
			;
	}
	newlen = length1 + length2 + 2;
	ntring = malloc(newlen * sizeof(char));
	if (ntring == NULL)
		return (NULL);
	for (a = 0; a < length1; a += 1)
		ntring[a] = strc1[a];
	ntring[a] = '/';
	for (b = 0; b < length2; b += 1)
		ntring[a + 1 + b] = strc2[b];
	ntring[length1 + length2 + 1] = '\0';
	return (ntring);
}

/**
 * _strlen - returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int _strlen(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++)
		;
	return (len);
}
