#include "ft_ls.h"

void	freef(void **item)
{
	t_file	*file;

	file = (t_file*)*item;
	if (!file)
		return ;
	free(file->name);
	free(file->path);
	if (file->stats)
		free(file->stats);
	free(file);
	*item = NULL;	
}
