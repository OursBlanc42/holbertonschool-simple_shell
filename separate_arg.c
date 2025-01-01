#include "tamagoshell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * separate_arg - splits a string into an array of arguments,
 * formatted to comply with Norme 89 standards
 * @string: the input string to be split into arguemnts
 * Return: return a pointer to an array of strings (arguments) or NULL
 */
char **separate_arg(char *string)
{
	char **child_argv = NULL;
	const char *separator = " ";
	int index = 0;
	int array_length = 0;
	int string_not_null = 0;

	char *argument_temp = NULL;

	/* check special case */
	if (string == NULL)
		return NULL;

	argument_temp = strtok(string, separator);
	while (argument_temp != NULL)
	{
		/* increase array by one word */
		array_length++;
		child_argv = realloc(child_argv, sizeof(char *) * array_length);
		if (child_argv == NULL)
			return (NULL);
		
		/*Alloc memory and copy argument in the array*/
		child_argv[index] = malloc(sizeof(char) * strlen(argument_temp) + 1);
		strcpy(child_argv[index], argument_temp);

		index++;

		/* next strtok call */
		argument_temp = strtok(NULL, separator);
	}

	/*Add a NULL at the end for execve*/
	array_length++;
	child_argv = realloc(child_argv, sizeof(char *) * array_length);
		if (child_argv == NULL)
		return (NULL);
	child_argv[array_length] = NULL;

	return (child_argv);
}
