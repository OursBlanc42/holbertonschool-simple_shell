#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * concat_path - Concatenates two strings with a "/" in between
 * Description:
 * 1 - Calculate the full length
 * 2 - Allocates memory according to length
 * 3 - Concatenate strings with / and store in a pointer
 * @base: The base path string.
 * @addendum: The string we want to add
 * Return: A pointer to the newly concatenated string, or NULL on failure.
 */
char *concat_path(const char *base, const char *addendum)
{
	/* Declare and initialize variables */
	size_t full_length = 0;
	char *result = NULL;

	/* Calculate length and allocate memory */
	full_length = strlen(base) + strlen("/") + strlen(addendum) + 1;
	result = malloc(full_length * sizeof(char));

	if (result == NULL)
	{
		printf("Error (malloc)");
		return (NULL);
	}

	/* Build the string */
	sprintf(result, "%s/%s", base, addendum);

	return (result);
}
