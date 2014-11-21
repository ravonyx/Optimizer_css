#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

t_maillon* new_maillon(char* name, int nb_keys, char** keys)
{
	t_maillon *new_m = (t_maillon*)malloc(sizeof(t_maillon));

	if(new_m == NULL)
	{
		printf("Allocation error\n");
		return NULL;
	}

	new_m->name = name;
	new_m->keys = keys;
	new_m->nb_keys = nb_keys;

	new_m->next = NULL;

	return new_m;
}

unsigned int linked_list_size(t_maillon* maillon)
{
    unsigned int length = 0;

    while(maillon != NULL)
    {
        maillon = maillon->next;
        length++;
    }

    return length;
}

void linked_list_display(t_maillon* maillon,t_bool display_beautiful,FILE* f_out) /* Print in f_out with, or without beautifully option */
{
	int i = 0;
	while(maillon != NULL)
	{
		if(display_beautiful)
			fprintf(f_out,"%s{\n",maillon->name);
		else
			fprintf(f_out,"%s{",maillon->name);
		for(i = 0; i < maillon->nb_keys; i++)
			if(display_beautiful)
				fprintf(f_out,"%s;\n", maillon->keys[i]);
			else
				fprintf(f_out,"%s;", maillon->keys[i]);
		maillon = maillon->next;
		if(display_beautiful)
			fprintf(f_out,"}\n");
		else
			fprintf(f_out,"}");
	}
	fclose(f_out);
}

t_maillon* add_maillon(t_maillon* maillon,t_maillon* new)
{
	t_maillon* save = maillon;
	if(new != NULL)
		while(maillon->next != NULL)
		{
			maillon = maillon->next;
		}
		maillon->next = new;
		
		return save;
}


t_maillon* delete_rule(t_maillon* maillon,int index)
{
	int i = 0;		
		char** new_keys = malloc(sizeof(char*)*(maillon->nb_keys-1));
		for(i =0;i < index;i++)/* Copy maillon->keys before index in new_keys*/
			{
				new_keys[i] = maillon->keys[i];
			}
		for(i = index+1;i < maillon->nb_keys;i++)/*restart copy after index value*/
			new_keys[i-1] = maillon->keys[i];
		free(maillon->keys);
		maillon->keys = new_keys;
		maillon->nb_keys = maillon->nb_keys - 1;
	return maillon;
}

void remove_empty(t_maillon* maillon)
{
	t_maillon* tmp = NULL;
	while(maillon->next != NULL) /*explore all list*/
	{
		if(maillon->next->nb_keys == 0) /* remove empty nodes */
		{
			tmp = maillon->next;
			maillon->next = maillon->next->next;
			
			free(tmp->keys);/* Free maillon->keys */
			free(tmp);		/* Free maillon */
		}
		else
			maillon = maillon->next;
	}
	if(maillon->nb_keys == 0)
		{
			maillon = NULL;
		}
}


int linked_list_get_by_name(t_maillon* maillon, char *name)
{
    int count = 0;

    while(maillon != NULL)
    {
        if(maillon->name == name)
            return count;

        count++;
        maillon = maillon->next;
        
    }

    return 0;
}

char* linked_list_get_by_position(t_maillon* maillon, unsigned int index, int* find)
{
    unsigned int count = 1;

    if(index > linked_list_size(maillon))
    {
        *find = 0;
        return 0;
    }

    while(count <= index)
    {
        count++;
        maillon = maillon->next;
    }

    return maillon->name;
}

void linked_list_free(t_maillon** maillon)
{
	int i;
	free((*maillon)->name);

	for(i = 0; i < (*maillon)->nb_keys; i++)
		free((*maillon)->keys[i]);
	free((*maillon)->keys);

	if((*maillon)->next != NULL)
		linked_list_free(& ((*maillon)->next));
	free(*maillon);
	*maillon = NULL;
}
