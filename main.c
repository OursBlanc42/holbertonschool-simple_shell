#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tamagoshell.h"
#include <string.h>

/**
* main - Entry point of the simple shell
* Description :
*	Check arguments
*	Display a prompt
*	Read user input
*	Call subfunction to clean string (remove \n character )
*	Call subfunction to execute the command
*@argc: number of argument
*@argv: array of argument
* Return: Always 0 (waiting abort (ctrl+c) or EOF (ctrl+d)
*/

int main(int argc, char **argv)
{
	char *string = NULL;
	char *string_copy = NULL;
	size_t buffer_size = 0;
	ssize_t readed;

	if (argc != 1)
	{
		printf("Please no argument\n");
		return (0);
	}

	while (1)
	{
		/* Show prompt only if are in terminal */
		if (isatty(STDIN_FILENO) == 1)
			printf("( ・‿・) > ");

		/* reset string buffer */
		if (string_copy != NULL)
		{
		free(string_copy);
		string_copy = NULL;
		}

		/* Waiting and read the input and check if succeed */
		readed = getline(&string, &buffer_size, stdin);
		if (readed == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				printf("\n");
			break;
		}

		/* Clean string and skip if the input is empty*/
		if (remove_newline(string) == NULL)
			continue;

		/* duplicate string before sending to execute */
		string_copy = strdup(string);
		if (string_copy == NULL)
		{
			perror("strdup");
			continue;
		}

		
		if (execute(string_copy, *argv) == 1)
			continue;

	}

	free(string);
	return (0);
}
