#include "tamagoshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "_which.h"

/**
 * execute - execute the command line
 *Description:
*	fork the current process
*	find the executable path with _which
*	execute the command line in child process
*	and wait the end of execve
*@string: string with the command line
*@av: argument with the name of shell
*Return: return 0 if sucess or 1 if fail
*/
int execute(char *string, char *av)
{
	__pid_t child_pid;

	char **child_argv = NULL;
	char *executable_path = NULL;

	/* Split string into arguments */
	child_argv = separate_arg(string);
	if (child_argv == NULL || child_argv[0] == NULL)
	{
        free_darray(child_argv);
		return (1);
	}

	/* Resolve the executable path using _which */
	executable_path = _which(child_argv[0]);
	if (executable_path == NULL)
	{
		fprintf(stderr, "%s: %s: command not found\n", av, child_argv[0]);
		free_darray(child_argv);
		return(1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(av);
		free_darray(child_argv);
		free(executable_path);
		return (1);
	}

	/* Child process: Execute the command */
	if (child_pid == 0)
	{
		if (execve(executable_path, child_argv, environ) == -1)
		{
			perror(av);
			free_darray(child_argv);
			free(executable_path);
			exit(EXIT_FAILURE);
		}
	}

	/* Parent process: Wait for child to finish */
	else
		wait(NULL);

	free_darray(child_argv);
	free(executable_path);
	return (0);
}
