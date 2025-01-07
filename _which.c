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
* 				and if not : searches for the location of an executable
*				in all the directories specified by the PATH environment
*				variable.
*
* Algorithm:
* 1. Check if the given input is an absolute path to an existing command
* 2. If not : split the PATH environment variable into a list of directories
* 3. For each directory in the list :  concatenate the input with PATH directory to
* form a full path (ex : /usr/bin/ + / + neofetch)
* 4. Check if this full path points to an existing command
* 5. If check succeed : return the full path of the command
* @target_program: The program name to search for
* Return :
* -> A string containing full path of program name if suceed
* -> Otherwise NULL (not found or error)
*/

char *_which(char *target_program)
{
	/* declare & initialize variable */
	char *var_env_name = "PATH";
	char *separator = ":";
	char *env_path = _getenv(var_env_name);
	list_t *head_path_list;
	list_t *path_list;
	struct stat buffer_stat;
	char *string_concat = NULL;
	char *resolved_path = NULL;

	/* Check if the input is a valid path and executable */
	if (stat(target_program, &buffer_stat) == 0)
	{
		resolved_path = strdup(target_program);
		return resolved_path;
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
			resolved_path = strdup(string_concat);
			free(string_concat);
			free_list(head_path_list);
			return (resolved_path);
		}

		free(string_concat);	/* Always free useless concatened string after use */
		path_list = path_list->next;	/*next node */
	}

	/* nothing was found return NULL and free everything*/
	free_list(head_path_list);
	return NULL;
}


