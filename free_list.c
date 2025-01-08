#include <stdlib.h>
#include "tamagoshell.h"

/**
* free_list - Free a list_t list
* Description :
* 1 - Loop through each node.
* 2 - Save the actual node in a buffer.
* 3 - Move forward to next node.
* 4 - Free memory of actual node.
*@head: pointer to a list_t list
*Return: void
*/
void free_list(list_t *head)
{
	list_t *temp_buffer = NULL;

	while (head != NULL)
	{
		temp_buffer = head->next;
		free(head->string);
		free(head);
		head = temp_buffer;
	}
}
