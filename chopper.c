#include <stdlib.h>
#include <string.h>
#include "_which.h"

/**
 * chopper - Splits a string into a linked list of words
 * Description: This function will split a string delimited by a separator
 * into words, and storing each word as a node in a linked list.
 * @string: Input string to be splitted
 * @separator: The delimiter used to split the string into words.
 * Return: A pointer to the head of the linked list containing the words.
 */

list_t *chopper(char *string, char *separator)
{
	/* declare & initialize variable */
	char *next_word = NULL;
	list_t *head = NULL;

	/* Loop in the printed result and separate each word in an linked list */
	next_word = strtok(string, separator);
	while (next_word != NULL)
	{
		add_node_end(&head, next_word);
		next_word = strtok(NULL, separator);
	}

	return (head);
}
