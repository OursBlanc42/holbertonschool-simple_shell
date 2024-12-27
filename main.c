#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tamagoshell.h"

/**
* main - Entry point of the simple shell
* Description :
*	Display a prompt
*	Read user input
*	Clean string (remove \n character )
*	Fork current process to child process and execute the command
*	Waiting child execution and display a prompt again
*@ac: number of argument
*@av: array of argument
*@env: environment local
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
			printf("\nヾ(• ֊ •) Good bye !\n");
			break;
		}

		/* clean string (remove last \n char) */
		string = remove_newline(string);

		if (execute(string, *av) == 1)
			continue;
	}
	free(string);
	return (0);
}
