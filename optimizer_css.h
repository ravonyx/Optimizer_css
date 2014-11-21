#ifndef OPTIMIZER_CSS_H
#define OPTIMIZER_CSS_H

#include "linked_list.h"

t_maillon* parser(char* filename, t_maillon *list, t_maillon **start_list);
void merge_on_name(t_maillon* maillon); 
void merge_on_attribute(t_maillon* maillon);

#endif
