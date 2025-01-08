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
	char **child_argv = NULL, *command_copy = NULL;

	command_copy = cpy_string(string);
	if (command_copy == 1)
		return (1);

	/* Split command_copy into arguments */
	child_argv = separate_arg(command_copy);
	if (child_argv == NULL || child_argv[0] == NULL)
	{
		free_memory(command_copy, child_argv);
		return (1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(av);
		free_memory(command_copy, child_argv);
		return (1);
	}

	/* Child process: Execute the command */
	if (child_pid == 0)
	{
		if (execve(child_argv[0], child_argv, environ) == -1)
		{
			perror(av);
			free_memory(command_copy, child_argv);
			free(string);
			exit(EXIT_FAILURE);
		}
	}

	/* Parent process: Wait for child to finish */
	else
		wait(NULL);
	free_memory(command_copy, child_argv);
	return (0);
}

/**
 * free_memory - free array alocate
 *@command: a string with the command
 *@child_argv: a double array wtith different argument separate
 */
void free_memory(char *command, char **child_argv)
{
	free(command);
	free_darray(child_argv);
}

/**
 * cpy_string - copy a string for manipulate
 *@string: string to copy
 *Return: return the copy
 */
char *cpy_string(char *string)
{
	char *command_copy;

	command_copy = strdup(string);
	if (command_copy == NULL)
	{
		perror("strdup");
		return (1);
	}

	return (command_copy);
}
