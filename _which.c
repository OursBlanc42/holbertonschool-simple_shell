#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tamagoshell.h"

/**
* cleanup_which - Free the variable
* Description: This subfunction will check each variable 
* nd free it if necessary
* @env_path: environnement path
* @head_path_list: head of single linked list
* @string_concat: concatened string
* Return: Nothing (void)
*/
void cleanup_which(char *env_path, list_t *head_path_list, char *string_concat)
{
	if (env_path != NULL)
		free(env_path);
	if (head_path_list != NULL)
		free_list(head_path_list);
	if (string_concat != NULL)
		free(string_concat);
}

/**
* _which - Rewrite of the `which` command
* Description: This program check if the given input is an executable;
*				and if not : searches for the location of an executable
*				in all the directories specified by the PATH environment
*				variable.
* Algorithm:
* 1. Check if the given input is an absolute path to an existing command
* 2. If not : split the PATH environment variable into a list of directories
* 3. For each directory in the list : concatenate the input with PATH directory
*	to form a full path (ex : /usr/bin/ + / + neofetch)
* 4. Check if this full path points to an existing command
* 5. If check succeed : return the full path of the command
* @target_program: The program name to search for
* Return:
* -> A string containing full path of program name if suceed
* -> Otherwise NULL (not found or error)
*/

char *_which(char *target_program)
{
	list_t *head_path_list = NULL, *path_list = NULL;
	char *separator = ":", *env_path = NULL;
	char *string_concat = NULL, *resolved_path = NULL;
	struct stat buffer_stat;

	/* Check if the input is a valid path and executable */
	if (stat(target_program, &buffer_stat) == 0)
		return (strdup(target_program));

	env_path = _getenv("PATH");
	if (env_path == NULL)
		return (NULL);

	head_path_list = chopper(env_path, separator);
	if (head_path_list == NULL)
	{
		free(env_path);
		return (NULL);
	}
	path_list = head_path_list;

	/* Loop through the list to find the executable */
	while (path_list != NULL)
	{
		string_concat = concat_path(path_list->string, target_program);

		if (string_concat == NULL)
		{
			cleanup_which(env_path, head_path_list, string_concat);
			return (NULL);
		}

		/* Check if the concatened path is an executable */
		if (stat(string_concat, &buffer_stat) == 0)
		{
			resolved_path = strdup(string_concat);
			cleanup_which(env_path, head_path_list, string_concat);
			return (resolved_path);
		}

		free(string_concat);
		string_concat = NULL;
		path_list = path_list->next;
	}

	cleanup_which(env_path, head_path_list, string_concat);
	return (NULL);
}


