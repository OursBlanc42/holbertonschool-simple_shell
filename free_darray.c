#include "tamagoshell.h"
#include <stdlib.h>

/**
 * free_darray- free a double array
 *@darray: the double array for free
 */
void free_darray(char **darray)
{
	int index = 0;

	if (darray == NULL)
		return;

	while (darray[index])
	{
		free(darray[index]);
		index++;
	}
	free(darray);
}
