#include "tamagoshell.h"
#include <stdio.h>


/**
* built_env - a function to display the environment variables
*@string: the string entered by the user (not used)
*Return: nothing (void)
*/
void built_env(char *string)
{
	(void)string;

	while (*environ)
	{
		printf("%s\n", *environ);
		environ++;
	}
}
