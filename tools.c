#include "libesgi/str_tools.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

int get_nb_keys(char* input)
{
	int	nb_keys = 0;
	int	i = 0;
	for(i = 0; input[i] != '\0'; i++)
	{
		if(input[i] == ';')
			nb_keys++;
		else if(input[i] == '}' && input[i-1] != ';')
			nb_keys++;
	}
	return nb_keys;
}

char* parser_keys(char* str_keys, char delim)
{
	char*	key = NULL;
	int	len = get_length_todelim(str_keys, delim);
	int 	len_to_malloc;

	if(delim == '}' && str_keys[len - 1] == ';')
	{
		key = malloc(len);
		len_to_malloc = len - 1;
	}
	else
	{
		key = malloc(len + 1);
		len_to_malloc = len;
	}
	
	my_memcpy(key, str_keys, len_to_malloc);
	if(key == NULL)
		return NULL;
	key[len_to_malloc] = '\0';
	return key;
}



char* remove_key_before(char* str_keys, int end_key)
{
	char*	new_input = NULL;
	int	len;
	char*	key_after_delim;
	int	len_to_end;

	if(end_key == 1)
		len = get_length_todelim(str_keys, '}');
	else
		len = get_length_todelim(str_keys, ';');
	

	key_after_delim = str_keys + (len + 1);
	len_to_end = length(key_after_delim);

	new_input = malloc(len_to_end + 1);
	if(new_input ==  NULL)
		return NULL;
	my_memcpy(new_input, key_after_delim, len_to_end + 1);
	free(str_keys);
	return new_input;
}


