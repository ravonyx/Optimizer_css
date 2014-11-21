#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef char t_bool;
#define TRUE 1
#define FALSE 0

typedef struct s_maillon
{
	char* name;
	int nb_keys;
	char** keys;
	struct s_maillon *next;
}t_maillon;


t_maillon* new_maillon(char* name, int nb_keys, char** keys);
unsigned int linked_list_size(t_maillon* maillon);
void linked_list_display(t_maillon* maillon,t_bool display_beautiful,FILE* f_out);
int linked_list_get_by_name(t_maillon* maillon, char *name);
char* linked_list_get_by_position(t_maillon* maillon, unsigned int index, int* find);
void linked_list_free(t_maillon** maillon);
t_maillon* delete_rule(t_maillon* maillon,int index);
t_maillon* add_maillon(t_maillon* maillon,t_maillon* new);
void remove_empty(t_maillon* maillon);
#endif //LINKED_LIST_H
