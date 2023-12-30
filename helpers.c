#include "shell.h"

/**
 * str_concat - Concatenate two strings
 * @s1: String 1
 * @s2: String 1
 * Return: Pointer to the concatenated string
 *
 * Overall this is helping in the validator.c file to check if a file exist
 * and if not continues to check the next file by taking two strings and
 * combines them returns a new string containing the concatenated strings
 */
char *str_concat(char *s1, char *s2)
{
	char *s;
	unsigned int i;
	unsigned int j;
	unsigned int k;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	for (i = 0; s1[i] != '\0'; i++)
		continue;

	for (j = 0; s2[j] != '\0'; j++)
		continue;

	j = j + 1;
	s = malloc((i + j) * sizeof(char));
	if (s == NULL)
		return (0);
	for (k = 0; k < (i + j) ; k++)
	{
		if (k < i)
			s[k] = s1[k];
		if (k >= i)
			s[k] = s2[k - i];
	}
	return (s);
}

/**
 * _realloc - Reallocate a memory block
 * @ptr: Pointer to array
 * @old_size: Old size
 * @new_size: New size
 * Return: A pointer to the allocated memory
 *
 * Overall this is used to resize a previous allocated memory block
 * taking care of operations in a safe way
 * Also provides option to free memory if new_size is 0
 */

 /*ptr is previous allocated memory block, old_size old size of the*/
 /* memory block, new_size new size of the memory block*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;
	char *ptr1;
	unsigned int i;

	ptr1 = (char *)ptr;
	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	s = malloc((new_size) * sizeof(char));
	if (s == NULL)
	{
		free(s);
		return (NULL);
	}
	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			s[i] = ptr1[i];
	}
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			s[i] = ptr1[i];
	}
	free(ptr1);
	return (s);
}
