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

	/* Split the command line into an array of arguments */
	child_argv = separate_arg(string);
	if (child_argv == NULL || child_argv[0] == NULL)
	{
		free(child_argv);
		printf("(╯°□°）╯︵ ┻━┻ (Invalid command)\n");
		return (1);
	}

	/* Resolve the executable path using _which */
	executable_path = _which(child_argv[0]);
	if (executable_path == NULL)
	{
		printf("(╯°□°）╯︵ ┻━┻ (Executable path not found by _which)\n");
		free_darray(child_argv);
		return (1);
	}

	/* fork current process and check if succeed */
	child_pid = fork();
	if (child_pid == -1)
	{
		printf("(╯°□°）╯︵ ┻━┻ (Error fork)\n");
		free_darray(child_argv);
		free(executable_path);
		return (1);
	}

	/* Execute the command in child process */
	if (child_pid == 0)
	{
		if (execve(executable_path, child_argv, environ) == -1)
		{
			printf("(╯°□°）╯︵ ┻━┻ (Execve error)\n");
			free_darray(child_argv);
			free(executable_path);
			exit(EXIT_FAILURE);
		}
	}

	/* waiting for child finish execution */
	else
		wait(NULL);

	free_darray(child_argv);
	free(executable_path);

	return (0);
}
