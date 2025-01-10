#include "tamagoshell.h"
#include <stdio.h>

/**
 * display_env - a function to display the env
 *Return: return nothing (void)
 */
void display_env(void)
{
	while (*environ)
	{
		printf("%s\n", *environ);
		environ++;
	}
}
