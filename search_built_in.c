#include "tamagoshell.h"
#include <stdlib.h>
#include <string.h>

/**
 * search_built_in - search if the string return to a function
 *@search: the string for search
 *Return: return a function pointer
 */
void (*search_built_in(char *search))(void)
{
	search_built b_disp[] = {
		{"env", display_env},
		{"exit", built_exit},
		{NULL, NULL},
		};
	int ind = 0;

	while (b_disp[ind].name_func != NULL)
	{
		if (search == b_disp->name_func)
			return (b_disp[ind].function_built);

		ind++;
	}
	return (NULL);
}
