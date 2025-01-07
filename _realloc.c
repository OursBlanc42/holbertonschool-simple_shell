#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * min - calculate minimum
 * Description : calculate minimum between 2 int
 * The function could be improved to take into account the == case,
 * but for the purpose we have here: no need.
 * @a: int 1
 * @b: int 2
 * Return: minimum between two values
 */

unsigned int min(unsigned int a, unsigned int b)
{
	if (a > b)
	{
		return (b);
	}
	else
	{
		return (a);
	}
}

/**
 * _realloc - Entry point : reallocates memory
 * Description : reallocates a memory block using malloc and free
 * @ptr: initial allocated memory
 * @old_size: size of the initial allocated memory
 * @new_size: size of the new allocated memory
 * Return:	pointer to the new allocated memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	/* declare variable */
	unsigned int i, minima;
	char *new_ptr = NULL;
	/* Convert void to char for byte-by-byte access (void* can't be deref'd) */
	char *src = (char *)ptr;

	if (new_size == old_size)
		return (ptr); /* if new_size == old_size do nothing and return ptr */

	if (ptr == NULL) /* If ptr is NULL, call is equiv. to malloc(new_size) */
	{
		new_ptr = malloc(new_size);
		return (new_ptr); /* no need to free 'cause ptr is NULL */
	}

	/* If new_size = 0 and ptr != NULL, call is like free(ptr). Return NULL */
	if ((new_size == 0) && (ptr != NULL))
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);	/* Allocate new memory block of "new_size" */
	if (new_ptr == NULL)
	{	/* check if memory allocation succeed */
		return (NULL);
	}
	else
	{	/* Copy old memory to new up to min of old/new sizes */
		/* Calculate min of old_size and new_size */
		minima = min(new_size, old_size);
		for (i = 0; i < minima ; i++)
		{
			new_ptr[i] = src[i];
		}
	}

	free(ptr); /* Free old memory no longer needed */

	return (new_ptr);
}
