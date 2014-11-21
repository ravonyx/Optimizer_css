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

char* merge_name(char* first,char* second)/* merge first and second string adding ',' as [first,second] */
{
	int k = 0;
	char* name = (char*)malloc(sizeof(char)*(length(first)+length(second)+2));
	for(k = 0; k < (length(first)+length(second)+2) ; k++)
	{
		if(k < length(first))
			name[k] = first[k];
	
		if(k == length(first))
			name[k] = ',';
		if(k > length(first))
			name[k] = second[k-length(first)-1];
		if(k == length(first)+length(second)+1)
			name[k] = '\0';
	
	}
	return name;
}

char* get_string_todelim(char* str, char delim)
{
	int	i = 0;
	int j = 0;
	char* result = NULL;
	if(str != NULL)
	{
		while(str[i++] != '\0' && str[i] != delim)
			;
	}
	result = (char*)malloc(sizeof(char)*i+1);
	for(j=0;j < i;j++)
	{
		result[j] = str[j];
	} 
	result[j] = '\0';
	return result;
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
		if(str[i] != '\n' && str[i] != '\t' && str[i] != ' ' && str[i] != '{' && str[i] != '}')
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

int my_strcmp(char* arg1, char* arg2)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while(arg2[j] != 0)
		j++;
	while(arg1[k] != 0)
		k++;

	while(arg1[i] !=0)
	{
		if(arg1[i] != arg2[i])
		{
			if(arg1[i]>arg2[i])
				return 1;
			else
				return -1;
		}
		i++;
	}
	if(k > j)
		return 1;
	if(j > k)
		return -1;
	return 0;
}
