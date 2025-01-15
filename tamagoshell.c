#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tamagoshell.h"
#include <string.h>

/**
* check_no_arg - Check if argument are passed to main
*@argc: number of argument
* Return: 1 if argument > 1
* 0 otherwise
*/
int check_no_arg(int argc)
{
	if (argc != 1)
	{
		fprintf(stderr, "Please no arguments\n");
		return (1);
	}
	return (0);
}


/**
* main - Entry point of the simple shell
* Description :
*	Check arguments
*	Display a prompt
*	Read user input
*	Call subfunction to clean string (remove \n character )
*	Call subfunction to execute the command
*@argc: number of argument
*@argv: array of argument
* Return: 0 (waiting abort (ctrl+c) or EOF (ctrl+d)
* or 1 if error (nb of arguments != 1)
*/
int main(int argc, char **argv)
{
	char *string = NULL, *string_copy = NULL;
	size_t buffer_size = 0;
	ssize_t readed;
	int line_number = 0;

	if (check_no_arg(argc) == 1)
		return (1);

	while (1)
	{
		prompt_user();

		readed = getline(&string, &buffer_size, stdin);
		if (end_file(readed) == 1)
			break;

		if (isatty(STDIN_FILENO) != 1)
			line_number++;

		if (remove_newline(string) == NULL)
			continue;

		if (check_built_in(string) == 1)
			continue;

		string_copy = strdup(string);
		if (string_copy == NULL)
		{
			perror("strdup");
			continue;
		}

		execute(string_copy, *argv, line_number);
		free(string_copy);
		string_copy = NULL;
	}
	free(string);
	return (0);
}

/**
 * check_built_in - function for reduce number of line
 *@string: the string for search if a function correspond
 *Return: return 1 if success or 0 if no builtin find
 */
int check_built_in(char *string)
{
	void (*function)(char *);

	function = search_built_in(string);
	if (function != NULL)
	{
		function(string);
		return (1);
	}
	return (0);
}

/**
 * prompt_user - a function for display the prompt for user
 *Description - Check if is an terminal and display if
 * is not a terminal
 *Return: return nothing
 */
void prompt_user(void)
{
	if (isatty(STDIN_FILENO) == 1)
		printf("( ・‿・) > ");
}

/**
 * end_file - Check if EOF is readed
 *@readed: the return of function getline
 *Return: return 1 if end of file is receive or 0
 */
int end_file(ssize_t readed)
{
	if (readed == -1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("\nヾ(• ֊ •) Good bye ! \n");
		return (1);
	}
	return (0);
}
