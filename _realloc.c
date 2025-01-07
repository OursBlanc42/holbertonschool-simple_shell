#include <stdlib.h>
#include <stdio.h>
#include "tamagoshell.h"

/**
 * min - calculate minimum
 * Description : calculate minimum between 2 int
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
 * _realloc - rewrite of realloc
 * Description : Reallocates memory
 * Algorithm :
 *		No change if new_size == old_size, returns ptr.
 *		If ptr == NULL, behaves like malloc(new_size).
 *		If new_size == 0 and ptr != NULL, frees ptr and returns NULL.
 *		Otherwise, allocates new memory like realloc
 * @ptr: Pointer to the initial allocated memory
 * @old_size: Size of the initial allocated memory
 * @new_size: Size of the new memory to allocate
 * Return:
 * -> Pointer to the newly allocated memory
 * -> NULL if allocation fails or if new_size is 0 and ptr is not NULL
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i, minima;
	char *new_ptr = NULL;
	/* Convert void to char for byte-by-byte access (void* can't be deref'd) */
	char *src = (char *)ptr;

	/* Case 1: No need to reallocate if sizes are identical */
	if (new_size == old_size)
		return (ptr);

	/* Case 2: Equivalent to malloc if ptr is NULL */
	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		return (new_ptr);
	}

	/* Case 3: Equivalent to free if new_size is 0 */
	if ((new_size == 0) && (ptr != NULL))
	{
		free(ptr);
		return (NULL);
	}

	/* Case 4: Allocate new memory like realloc */
	new_ptr = malloc(new_size);

	if (new_ptr == NULL)
		return (NULL);

	/* Copy data to the smaller size to avoid out of bounds */
	minima = min(new_size, old_size);
	for (i = 0; i < minima ; i++)
		new_ptr[i] = src[i];

	free(ptr);

	return (new_ptr);
}
