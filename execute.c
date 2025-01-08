#include "tamagoshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
* execute - execute the command line
* Description:
*     Forks the current process, executes the command in the child process,
*     and waits for the child process to finish.
* @string: Command line string (should not be freed here)
* @av: Name of the shell program
* Return: 0 if success, 1 if failure
*/
int execute(char *string, char *av)
{
	__pid_t child_pid;
	char **child_argv = NULL;
	char *command_copy = NULL;

	/* Create a copy of the command string */
	command_copy = strdup(string);
	if (command_copy == NULL)
	{
		perror("strdup");
		return (1);
	}

	/* Split command_copy into arguments */
	child_argv = separate_arg(command_copy);
	if (child_argv == NULL || child_argv[0] == NULL)
	{
		free(command_copy);
		free_darray(child_argv);
		return (1);
	}

	/* Fork the current process */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror(av);
		free(command_copy);
		free_darray(child_argv);
		return (1);
	}

	/* Child process: Execute the command */
	if (child_pid == 0)
	{
		if (execve(child_argv[0], child_argv, environ) == -1)
		{
			perror(av);
			free(command_copy);
			free_darray(child_argv);
			exit(EXIT_FAILURE);
		}
	}

	/* Parent process: Wait for child to finish */
	else
	{
		wait(NULL);
	}

	/* Free resources */
	free(command_copy);
	free_darray(child_argv);
	return (0);
}
