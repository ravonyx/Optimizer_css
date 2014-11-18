#include "libesgi/str_tools.h"
#include "linked_list.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

typedef char t_bool;
#define TRUE 1
#define FALSE 0

t_maillon* parser(char* filename, t_maillon *list, t_maillon **start_list);

int main(int argc, char** argv)
{
	t_maillon*	list_tag = NULL;
	t_maillon*	start_list = NULL;
	//FILE* 	f_out;
	int		i = 1;
	int		nb_files = argc - 1;

	printf("Number of files: %d\n", nb_files);
	while(i <= nb_files)
	{
		list_tag = parser(argv[i], list_tag, &start_list);
		i++;
	}

	/*if (NULL == (f_out = fopen(argv[argc - 1],"wb"))) 
	{
		fprintf(stderr,"Fail to open file in writing\n");
		exit(1);
	}*/
	
	//free(f_out);
	linked_list_display(start_list);
	linked_list_free(&start_list);
	return 0;
}



//Parse en prenant en compte les carac '{' et '}'
t_maillon* parser(char* filename, t_maillon *list, t_maillon** start_list)
{
	FILE* 		fp;
	char*		title = NULL;
	char*		str_keys = NULL;
	char**		keys = NULL;
	size_t		len = 0;
	ssize_t 	read= 0;
	int		i;
	int		nb_keys = 0;
	t_maillon	*new_node;

	fp = fopen(filename,"r");

	if (NULL == fp) 
	{
		fprintf(stderr,"Fail to open file in reading\n");
		exit(1);
	}
	
	while(read != -1)
	{
		
		read = getdelim(&title, &len, '{', fp);
		read = getdelim(&str_keys, &len, '}', fp);
		if(read != -1)
		{
			title = delete_space(title);
			str_keys = delete_space(str_keys);
			nb_keys = get_nb_keys(str_keys); //retourne le nombre de clés
			keys = malloc(nb_keys * sizeof(char*));

			for(i = 0; i < nb_keys; i++)
			{
				keys[i] = parser_keys(str_keys); // parser avec ; retourner char* chaine de une key
				str_keys = remove_key_before(str_keys);
			}

			new_node = new_maillon(title, nb_keys, keys);
			if(list != NULL)
				list->next = new_node;
			list = new_node;
			if(*start_list == NULL)
				*start_list = list;
			
			free(str_keys);
			str_keys = NULL;
			title = NULL;
		}
		else
		{
			free(title);
			free(str_keys);
		}
	}
	fclose(fp);
	return list;
}

