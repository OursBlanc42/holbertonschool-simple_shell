#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "_which.h"
#include "find.h"

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
	char *separator = ":";
	char *env_path = NULL;
	struct stat buffer_stat;
	list_t *head_path_list = NULL, *path_list = NULL;
	char *string_concat = NULL, *resolved_path = NULL;

	/* Check if the input is a valid path and executable */
	if (stat(target_program, &buffer_stat) == 0)
		return (strdup(target_program));

	/* call env_path */
	env_path = _getenv("PATH");
	if (env_path == NULL)
		return (NULL);

	/* Generate path list */
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

		if (string_concat == NULL)	/* Check special case (error) */
		{
			free_list(head_path_list);
			free(env_path);
			return (NULL);
		}

		/* Check if the concatened path is an executable */
		if (stat(string_concat, &buffer_stat) == 0)
		{
			resolved_path = strdup(string_concat);
			free(string_concat);
			free_list(head_path_list);
			free(env_path);
			return (resolved_path);
		}

		free(string_concat);
		path_list = path_list->next;
	}

	free(env_path);
	free_list(head_path_list);
	return (NULL);
}


