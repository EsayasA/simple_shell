#include "shell.h"
/**
 * buffer_free - frees the buffer
 * @p:pointer
 * Return:1 if ok 0 if failed
 */
int buffer_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
