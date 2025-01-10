#include "tamagoshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/**
 * print_not_found - show the specific output when function is not found
 * @argv: name of the program
 * @child_argv: a double array wtith different argument separate
 * @line_number: number of the line where the problem occur
 * Return: Nothing (void)
 */
void print_not_found(const char *argv, const char *child_argv, int line_number)
{
	if (line_number > 0)
		fprintf(stderr, "%s: %d: %s: not found\n", argv, line_number, child_argv);
	else
		fprintf(stderr, "%s: %s: not found\n", argv, child_argv);
}

/**
 * execute - execute the command line
 *Description:
*	fork the current process
*	find the executable path with _which
*	execute the command line in child process
*	and wait the end of execve
*@string: string with the command line
*@argv: argument with the name of shell
* @line_number: number of the line where the problem occur
*Return: return 0 if sucess or 1 if fail
*/
int execute(char *string, char *argv, int line_number)
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
		print_not_found(argv, child_argv[0], line_number);
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
