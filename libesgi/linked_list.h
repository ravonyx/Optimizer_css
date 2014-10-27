#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct s_maillon
{
    int data;
    struct s_maillon *next;
}t_maillon;

t_maillon* new_maillon(int data);
unsigned int linked_list_size(t_maillon* maillon);
void linked_list_display(t_maillon* maillon);
int linked_list_get_by_value(t_maillon* maillon, int value);
int linked_list_get_by_position(t_maillon* maillon, unsigned int index, int* find);
void linked_list_free(t_maillon** maillon);

#endif //LINKED_LIST_H