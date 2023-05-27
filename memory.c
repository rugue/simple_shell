#include "shell.h"

/**
 * bfree - this release pointer and NULLs adress
 * @ptr: adress of point to release
 *
 * Return: 1 if released, otherwise 0zero
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
/** updated memory.c **/
