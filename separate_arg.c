#include "tamagoshell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * separate_arg - separate the different arg in the array for norme 89
 *@string: the string for separate
 *Return: return a pointer of array or NULL if fail
 */
char **separate_arg(char *string)
{
	char **child_argv = NULL;
	const char *separator = " ";
	char *argument_temp = NULL;
	int index = 0;
	int array_length = 0;
	int string_not_null = 0;

	/*Loop for separate the argument in an array*/
	while (string_not_null != 1)
	{
		argument_temp = strtok(string, separator);
		string = NULL;

		if (argument_temp == NULL)
		{
			string_not_null = 1;
			break;
		}
		/* increase array by one word */
		array_length++;
		child_argv = realloc(child_argv, sizeof(char *) * array_length);
		if (child_argv == NULL)
			return (NULL);

		/*Alloc memory and copy argument in the array*/
		child_argv[index] = malloc(sizeof(char) * strlen(argument_temp) + 1);
		strcpy(child_argv[index], argument_temp);
		argument_temp = NULL;

		index++;
	}

	/*Add a NULL at the end for execve*/
	array_length++;
	child_argv = realloc(child_argv, sizeof(char *) * array_length);
	child_argv[array_length] = NULL;

	return (child_argv);
}
