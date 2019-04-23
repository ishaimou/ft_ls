#include "ft_ls.h"

void	print_item(void *item)
{
	t_file	*file;

	file = (t_file*)item;
	ft_printf("%s\n", file->name);
}
