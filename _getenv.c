#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "find.h"

/**
 * _getenv - search a variable in the environnement
 *@search: the variable you search
 *Return: return a pointer to the the variable
 */
char *_getenv(const char *search)
{
	char **ptr_env = environ;
	char *sep_equal = NULL;
	char *cpy_var = NULL;

	/*browse the environnement with a pointer and search = in the current string*/
	while (*ptr_env != NULL)
	{
		sep_equal = strchr(*ptr_env, '=');

		/**
		* If the separator if find and  the name of variable correspond
		* return the string after the separator
		*/
		if (sep_equal != NULL && strncmp(*ptr_env, search, strlen(search)) == 0)
		{
			cpy_var = malloc(strlen(sep_equal + 1) * sizeof(char) + 1);
			strcpy(cpy_var, sep_equal + 1);
			return (cpy_var);
		}

		ptr_env++;
	}
	return (NULL);
}
