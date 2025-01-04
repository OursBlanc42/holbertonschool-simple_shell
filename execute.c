#include "tamagoshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute - execute the command line
 *Description:
 *	fork the current process
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

	child_argv = separate_arg(string);
	if (child_argv == NULL || child_argv[0] == NULL)
	{
		free(child_argv);
		return (1);
	}

	/* fork current process and check if succeed */
	child_pid = fork();
	if (child_pid == -1)
	{
		printf("(╯°□°）╯︵ ┻━┻ (Error fork)\n");
		free_darray(child_argv);
		return (1);
	}

	/* Execute the command in child process */
	if (child_pid == 0)
	{
		if (execve(child_argv[0], child_argv, environ) == -1)
		{
			printf("%s: 1: %s: not found\n", av, child_argv[0]);
			free_darray(child_argv);
			exit(EXIT_FAILURE);
		}
	}

	/* waiting for child finish execution */
	else
		wait(NULL);
	free_darray(child_argv);
	return (0);
}