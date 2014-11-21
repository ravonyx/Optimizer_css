#include "libesgi/str_tools.h"
#include "linked_list.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>



t_maillon* parser(char* filename, t_maillon *list, t_maillon **start_list);
void merge_on_name(t_maillon* maillon); 
void merge_on_attribute(t_maillon* maillon);

int main(int argc, char** argv)
{
	t_maillon*	list_tag = NULL;
	t_maillon*	start_list = NULL;
	t_bool display_beautiful = FALSE;
	FILE* 	f_out;
	int		i = 1;
	int		nb_files = argc - 2; /* Ignore result file and program name */
	int 		i_file;
	
	if(argc == 1)
	{
		printf("Unknown Option, usage: optimizer_css [-h] [-b] css_in ... css_out\n");	
		return -1;	
	}
	
	if(my_strcmp(argv[i], "-h") == 0)
	{
		printf("usage: optimizer_css [-h] [-b] css_in ... css_out\n");		
		return 0;
	}
	
	else if(my_strcmp(argv[i], "-b") == 0)
	{
		display_beautiful = TRUE;
		nb_files --;
		i++;
	}

	if(nb_files <= 0) 
	{
		fprintf(stderr,"Not enough arguments [-h] for usage\n");
		return -1;
	}

	for(i_file = 0; i_file < nb_files; i_file++)
	{
		list_tag = parser(argv[i], list_tag, &start_list);
		if(list_tag == NULL)
			return -1;
		i++;
	}
	if (NULL == (f_out = fopen(argv[argc-1],"w"))) 
	{
		fprintf(stderr,"Fail to open file %s in writing\n",argv[argc-1]);
		exit(1);
	}
	
	/*-----------------------Merge On Name-----------------------------------*/
	merge_on_name(start_list);
	/*-----------------------Merge On Attribute------------------------------*/
	merge_on_attribute(start_list);	
	/*-----------------------Remove empty------------------------------*/
	remove_empty(start_list);
	/*-----------------------Display in file-----------------------------------*/
	linked_list_display(start_list,display_beautiful,f_out);
	linked_list_free(&start_list);
	return 0;
}


t_maillon* parser(char* filename, t_maillon *list, t_maillon** start_list)/* Parse on '{' and '}' */
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
		return NULL;
	}
	
	while(read != -1)
	{
		
		read = getdelim(&title, &len, '{', fp);
		if(read == -1)
		{
			free(title);
			free(str_keys);
			printf("Read error\n");
			continue;
		}
		read = getdelim(&str_keys, &len, '}', fp);
		if(read != -1)
		{
			title = delete_space(title);
			str_keys = delete_space(str_keys);
			nb_keys = get_nb_keys(str_keys); //retourne le nombre de clés
			keys = malloc(nb_keys * sizeof(char*));
			if(keys == NULL)
				return NULL;

			for(i = 0; i < nb_keys; i++)
			{
				keys[i] = parser_keys(str_keys); // parser avec ; retourner char* chaine de une key
				if(keys[i] == NULL)
					return NULL;
				str_keys = remove_key_before(str_keys);
				if(str_keys == NULL)
					return NULL;
			}

			new_node = new_maillon(title, nb_keys, keys);
			if(new_node == NULL)
				return NULL;
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

void merge_on_name(t_maillon* maillon) /* Merge maillon on name */
{
	t_maillon* in_use = NULL;
	t_maillon* last = NULL;
	char ** keys = NULL;
	int i = 0;
	int j = 0;
	int k = 0;
	int conflict = 0;
	int nb_conflict = 0;
	/*int choice = 0; unused variable when choice block disabled */
	do 
	{
		in_use = maillon;
		last = in_use;
		maillon = maillon->next;
		while(maillon!=NULL)
		{
			if(my_strcmp(maillon->name,in_use->name) == 0)
				{
					keys = malloc(sizeof(char*)*(maillon->nb_keys + in_use->nb_keys));
					for(i=0;i < in_use->nb_keys;i++)
					{
						keys[i] = in_use->keys[i];
					}
					for(j=0;j < maillon->nb_keys;j++)
					{
						
						for(k=0;k < in_use->nb_keys;k++)
						{
							
							if(my_strcmp(get_string_todelim(keys[k],':'),get_string_todelim(maillon->keys[j],':')) == 0)
							{
								conflict = 1;
								nb_conflict++;
								
								
							/*	Conflict choice 
							 * 
							 * printf("Conflicting key %s in %s \n Press 1 for %s \n Press 2 for %s ",get_string_todelim(keys[k],':'),in_use->name,in_use->keys[k],maillon->keys[j]);
							 *	scanf("%d",&choice);
							 *	if(choice == 1)
							 *	{
							 *		keys[k] = in_use->keys[k];
							 *	}
							 *	else if(choice ==2)
							 *  AUTO SELECT SECOND FILE*/
									keys[k] = maillon->keys[j];
							}
						}
						if(!conflict)
							keys[i+j] = maillon->keys[j];
						conflict = 0 ;
					} 
					in_use->keys = keys;
					in_use->nb_keys = (maillon->nb_keys + in_use->nb_keys)-nb_conflict;
					nb_conflict = 0;
					if(maillon->next!=NULL)
						last->next = maillon-> next;
					else
						last->next = NULL;
				}
			last = maillon;
			maillon = maillon->next;
		}
		maillon = in_use;
		maillon = maillon->next;
		
	}
	while(maillon!=NULL);
	
}

void merge_on_attribute(t_maillon* maillon) /* make each attribute unique */
{
	t_maillon* in_use = NULL;
	t_maillon* new = NULL;;
	char ** keys = NULL;
	char* name = NULL;
	int i = 0;
	int j = 0;
	int found = 0;
	
	while(maillon->next !=NULL) /* For each "maillon" except the last one */
	{
		in_use = maillon; /* Saving in_use node */
		maillon = in_use->next;
		for(i = 0; i < in_use->nb_keys ; i++) /* Looking at each keys */
		{
			maillon = in_use->next; /* Start research on next node */
			
			while(maillon != NULL) /* For each rule looking at other "maillon" */
			{
				for(j = 0; j < maillon->nb_keys && found == 0 ; j++) /* compare in_use->keys[i] with maillon->keys[j] and stop on match*/
				{
					
					if(my_strcmp(in_use->keys[i],maillon->keys[j]) == 0)
					{
						
						keys = malloc(sizeof(char*)*1);
						keys[0] = in_use->keys[i];					
						name = merge_name(maillon->name,in_use->name);
						new = new_maillon(name,1,keys);
						maillon = add_maillon(maillon,new);					
						in_use = delete_rule(in_use,i);
						maillon = delete_rule(maillon,j);
						
						found = 1; /* Bool match found */
						
					}
				}
		
				if(found) /* Stop search when match found */
				{
					found = 0;
					break;
				}
				if(maillon!= NULL)
					maillon = maillon->next;
			}		
		}
		
		maillon = in_use;
		maillon = maillon->next;		
	}
}
