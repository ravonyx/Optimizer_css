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
	}
	return nb_keys;
}

char* parser_keys(char* str_keys)
{
	char*	key = NULL;
	int	len = get_length_todelim(str_keys, ';');

	key = malloc(len + 1);
	if(key == NULL)
		return NULL;
	my_memcpy(key, str_keys, len);
	key[len] = '\0';
	return key;
}



char* remove_key_before(char* str_keys)
{
	char*	new_input = NULL;
	int	len = get_length_todelim(str_keys, ';');
	char*	key_after_delim = str_keys + (len + 1);
	int	len_to_end = length(key_after_delim);

	new_input = malloc(len_to_end + 1);
	if(new_input ==  NULL)
		return NULL;
	my_memcpy(new_input, key_after_delim, len_to_end + 1);
	free(str_keys);
	return new_input;
}


