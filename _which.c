#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "_which.h"
#include "find.h"

/**
 * main - Entry point - Rewrite of the `which` command
 * Description: This program searches for the location of an executable
 *				in all the directories specified by the PATH environment
 *				variable.
 *
 * Algorithm:
 * 1. Check if the input is an absolute valid path (return the path if succeed)
 * 2. Split the PATH environment variable into a list of directories.
 * 3. For each dir, concatenate the full path (ex : /usr/bin/ + / + neofetch)
 * 4. For each full path, check with "stat" if the executable exist.
 * 5. Return the full path of the command if found; print an error otherwise.
 * @argc: The number of arguments passed to the program.
 * @argv: An array of strings representing the arguments passed to the program.
 * Return: 
 * -> Full path of program name from target program name if suceed
 * -> Otherwise NULL (not found)
 */

char *_which(char *target_program)
{
	/* declare & initialize variable */
	char *var_env_name = "PATH";
	char *separator = ":";
	char *env_path = ___int_size_t_h(var_env_name);
	list_t *head_path_list;
	list_t *path_list;
	struct stat buffer_stat;
	char *string_concat = NULL;
	int index;
	int founded = 0;
	int fail = 0;

	/* Check if the input is a valid path and executable */
	if (stat(target_program, &buffer_stat) == 0)
	{
		return (target_program);
	}

	/* generate path list and stock in single linked list */
	head_path_list = chopper(env_path, separator);

	/* duplicate to not loose the head */
	path_list = head_path_list;

	/* Loop through the linked list and check if the programm exist */
	while (path_list != NULL)
	{
		/* concatenate the begining of the path with target_program name to generate an available full path */
		string_concat = concat_path(path_list->string, target_program);

		/* check special case error */
		if (string_concat == NULL)
		{
			free_list(head_path_list);
			return NULL;
		}

		/* if the executable is found (with stat) stop the research */
		if (stat(string_concat, &buffer_stat) == 0)
		{
			free_list(head_path_list);
			return (string_concat);
		}

		free(string_concat);	/* Always free string after use */
		string_concat = NULL; /* Reset string_concat to avoid double free*/
		path_list = path_list->next;	/*next node */
	}

	/* nothing was found return NULL and free everything*/
	free_list(head_path_list);
	return NULL;
}


