#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "tamagoshell.h"

/**
* main - Entry point of the simple shell
* Description :
*	Display a prompt
*	Read user input
*	Clean string (remove \n character )
*	Fork current process to child process and execute the command
*	Waiting child execution and display a prompt again
* Return: Always 0 (waiting abort (ctrl+c) or EOF (ctrl+d)
*/

int main(int ac, char **av, char **env)
{
	char *string = NULL;
	size_t buffer_size = 0;
	ssize_t readed;
	pid_t child_pid;
	int index = 0;
	char *child_argv[2];

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
		for (index = 0; string[index] != '\0'; index++)
		{
			if (string[index] == '\n')
				string[index] = '\0';
		}

		/* fork current process and check if succeed */
		child_pid = fork();
		if (child_pid == -1)
		{
			printf("(╯°□°）╯︵ ┻━┻ (Error fork)\n");
			free(string);
			continue;
		}

		/* Execute the command in child process */
		if (child_pid == 0)
		{
			child_argv[0] = string;
			child_argv[1] = NULL;
			if (execve(child_argv[0], child_argv, env) == -1)
			{
				printf("%s: 1: %s: not found\n", av[0], child_argv[0]);
				free(string);
				exit(EXIT_FAILURE);
			}
		}

		/* waiting for child finish execution */
		else
		{
			wait(NULL);
			free(string);
			string = NULL;
		}
	}
	free(string);
	return (0);
}
