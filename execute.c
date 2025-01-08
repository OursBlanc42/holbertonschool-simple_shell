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
	char **child_argv = NULL, *string_copy = NULL;

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
		if (execve(child_argv[0], child_argv, environ) == -1)
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
