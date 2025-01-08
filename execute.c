#include "tamagoshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
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

	char **child_argv = NULL, *string_copy = NULL;
	char *executable_path = NULL;

	string_copy = duplicate_string(string);
	if (string_copy == NULL)
		return (1);

	/* Split string_copy into arguments */
	child_argv = separate_arg(string_copy);
	if (child_argv == NULL || child_argv[0] == NULL)
	{
		free_memory(string_copy, child_argv);
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
		free_memory(string_copy, child_argv);
		return (1);
	}

	/* Child process: Execute the command */
	if (child_pid == 0)
	{
		if (execve(executable_path, child_argv, environ) == -1)
		{
			perror(av);
			free_memory(string_copy, child_argv);
			free(string);
			exit(EXIT_FAILURE);
		}
	}

	/* Parent process: Wait for child to finish */
	else
		wait(NULL);
	free_memory(string_copy, child_argv);
	return (0);
}

/**
 * free_memory - free array alocate
 * @command: a string with the command
 * @child_argv: a double array wtith different argument separate
 * Return: Nothing (void)
 */
void free_memory(char *command, char **child_argv)
{
	free(command);
	free_darray(child_argv);
}

/**
* duplicate_string - string to duplicate
* @string: the string to duplicate
* Return: a copy of the string or NULL if error
*/
char *duplicate_string(const char *string)
{
	char *string_copy = strdup(string);

	if (string_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	return (string_copy);
}
