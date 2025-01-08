#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tamagoshell.h"

/**
* main - Entry point of the simple shell
* Description :
*	Check arguments
*	Display a prompt
*	Read user input
*	Call subfunction to clean string (remove \n character )
*	Call subfunction to execute the command
*@ac: number of argument
*@av: array of argument
* Return: Always 0 (waiting abort (ctrl+c) or EOF (ctrl+d)
*/

int main(int ac, char **av)
{
	char *string = NULL;
	size_t buffer_size = 0;
	ssize_t readed;

	if (ac != 1)
	{
		printf("Please no argument\n");
		return (0);
	}

	while (1)
	{
		/* Show prompt only if are in terminal */
		if (isatty(STDIN_FILENO) == 1)
			printf("( ・‿・) > ");

		/* Waiting and read the input and check if succeed */
		readed = getline(&string, &buffer_size, stdin);
		if (readed == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
			{
				printf("\n");
			}
			break;
		}

		/* clean string (remove last \n char) */
		if (remove_newline(string) == NULL)
		{
			continue; /* Skip to next iteration if string is NULL or empty */
		}

		/* call subfunction to execute command */
		if (execute(string, *av) == 1)
		{
			continue;
		}
			
	}
	
	free(string);
	return (0);
}
