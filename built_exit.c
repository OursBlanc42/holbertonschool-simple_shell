#include "tamagoshell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * built_exit - a function to exit the shell
 * Description: cause normal process termination
 * @string: user input (should be 'exit')
 * Return: return nothing
 */
void built_exit(char *string)
{
	if (string != NULL)
		free(string);

	if (isatty(STDIN_FILENO) == 1)
		printf("\nヾ(• ֊ •) Good bye ! \n");

	exit(0);
}