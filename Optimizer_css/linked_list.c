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

//TO CHANGE
void linked_list_display(t_maillon* maillon)
{
	int i = 0;
	while(maillon != NULL)
	{
		printf("Name of tag:%s\n", maillon->name);
		printf("number of keys: %d\n", maillon->nb_keys);

		for(i = 0; i < maillon->nb_keys; i++)
			printf("Key: %s\n", maillon->keys[i]);
		maillon = maillon->next;
	}
	printf("\n");
}

//TO CHANGE
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
