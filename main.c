#include "libesgi/str_tools.h"
#include "linked_list.h"
#include "optimizer_css.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

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
		printf("-b beautify\n-h display this screen \n");		
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

	printf("Parser done");
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
	merge_on_name(start_list);

	linked_list_display(start_list,display_beautiful,f_out);
	linked_list_free(&start_list);
	return 0;
}



