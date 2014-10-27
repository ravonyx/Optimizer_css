#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

t_maillon* new_maillon(int data)
{
    t_maillon *new_m = (t_maillon*)malloc(sizeof(t_maillon));


    if(new_m == NULL)
    {
        printf("Allocation error\n");
        return NULL;
    }

    new_m->data = data;
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

void linked_list_display(t_maillon* maillon)
{
    while(maillon != NULL)
    {
        printf("%d ", maillon->data);
        maillon = maillon->next;
    }
}

int linked_list_get_by_value(t_maillon* maillon, int value)
{
    int count = 0;

    while(maillon != NULL)
    {
        if(maillon->data == value)
            return count;

        count++;
        maillon = maillon->next;
    }

    return 0;
}

int linked_list_get_by_position(t_maillon* maillon, unsigned int index, int* find)
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

    return maillon->data;
}

void linked_list_free(t_maillon** maillon)
{
    if((*maillon)->next != NULL)
        linked_list_free(& ((*maillon)->next));

    free(*maillon);
    *maillon = NULL;
}