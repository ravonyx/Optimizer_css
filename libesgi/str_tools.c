#include "str_tools.h"
#include <stdio.h>
#include <stdlib.h>

int get_length_todelim(char* str, char delim)
{
	int	i = 0;

	if(str != NULL)
	{
		while(str[i++] != '\0' && str[i] != delim)
			;
	}
	return i;
}

void my_memcpy(char* dst, char* src, int len)
{
	int	i = 0;

	for(i = 0; i < len; i++)
	{
		dst[i] = src[i];
	}
}

int length(char* chaine)
{
	int	i = 0;

	for(i = 0; chaine[i] != '\0'; i++)
		;
	return i;
}

char* delete_space(char* str)
{
	int	i = 0;
	int	j = 0;
	int	size_result;
	char*	result = NULL;

	while(str[i] != '\0')
	{
		if(str[i] != 32 && str[i] != 9 && str[i] != '{' && str[i] != '}')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	size_result = length(str) + 1;
	result = malloc(size_result);
	if(result != NULL)
		my_memcpy(result, str, size_result);
	free(str);
	return result;
}
