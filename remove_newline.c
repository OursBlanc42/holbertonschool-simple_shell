#include <stddef.h>

/**
 * remove_newline - remove the newline char in a string
 *Description:
 *	Search a newline character in a string
 *	and if find it change newline character
 *	by null character ('\0) check also if string is empty
 *@string: the string for search
 *Return: return a pointer of string after changement
 */

char *remove_newline(char *string)
{
	int index;

	if ((string == NULL) || (string[0] == '\0'))
	{
		return (NULL);
	}

	for (index = 0; string[index] != '\0'; index++)
	{
		if (string[index] == '\n')
			string[index] = '\0';
	}

	return (string);
}
