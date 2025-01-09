#include "tamagoshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute - execute the command line
 *Description:
*	fork the current process
*	find the executable path with _which
*	execute the command line in child process
*	and wait the end of execve
*@string: string with the command line
*@argv: argument with the name of shell
*Return: return 0 if sucess or 1 if fail
*/
int execute(char *string, char *argv)
{
	__pid_t child_pid;
	char **child_argv = NULL, *executable_path = NULL;

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
		fprintf(stderr, "%s: %s: command not found\n", argv, child_argv[0]);
		free_darray(child_argv);
		return (1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		cleanup_error(executable_path, child_argv, argv);
		return (1);
	}
	else if (child_pid == 0)
	{
		if (execve(executable_path, child_argv, environ) == -1)
		{
			cleanup_error(executable_path, child_argv, argv);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);

	free_darray(child_argv);
	free(executable_path);
	return (0);
}

/**
 * cleanup_error - free array alocate
 * @exec_path: a string with the command
 * @child_argv: a double array wtith different argument separate
 * @argv: name of executable for error message
 * Return: Nothing (void)
 */
void cleanup_error(char *exec_path, char **child_argv, char *argv)
{
	perror(argv);
	free(exec_path);
	free_darray(child_argv);
}
