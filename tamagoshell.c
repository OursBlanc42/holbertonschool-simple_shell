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
* Return: 0 (waiting abort (ctrl+c) or EOF (ctrl+d) 
* or 1 if error (nb of arguments != 1)
*/

int main(int argc, char **argv)
{
	char *string = NULL, *string_copy = NULL;
	size_t buffer_size = 0;
	ssize_t readed;
	int line_number = 0;

	if (argc != 1)
	{
		fprintf(stderr, "Please no arguments\n");
		return (1);
	}
	
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("( ・‿・) > ");

		/* Waiting and read the input and check if succeed */
		readed = getline(&string, &buffer_size, stdin);
		if (readed == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				printf("\nヾ(• ֊ •) Good bye ! \n");
			break;
		}

		if (isatty(STDIN_FILENO) != 1)
			line_number++;

		if (remove_newline(string) == NULL)
			continue;

		string_copy = strdup(string);
		if (string_copy == NULL)
		{
			perror("strdup");
			continue;
		}

		execute(string_copy, *argv, line_number);

		free(string_copy);
		string_copy = NULL;

	}
	free(string);
	return (0);
}
