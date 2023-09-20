#include "shell.h"
/**
 * re_alloc - it reallocs a memory
 * @p: pointer to malloc
 * @old:it is previous block
 * @new: it is new block
 * Return: p to the memory.
 */
void *re_alloc(void *p, unsigned int old, unsigned int new)
{
	char *h;

	if (!p)
		return (malloc(new));
	if (!new)
		return (free(p), NULL);
	if (new == old)
		return (p);

	h = malloc(new);
	if (!h)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		h[old] = ((char *)p)[old];
	free(p);
	return (h);
}
/**
 *my_memset - it occupied memory
 *@ptr: it is pointor
 *@byte:bytes
 *@n: number of byte
 *Return: ptr
 */
char *my_memset(char *ptr, char byte, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		ptr[j] = byte;
	return (ptr);
}

/**
 * _free - uses to give freedom to string
 * @h: string
 */
void _free(char **h)
{
	char **s = h;

	if (!h)
		return;
	while (*h)
		free(*h++);
	free(s);
}


