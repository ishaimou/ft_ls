#include "ft_ls.h"

void	print_item(void *item)
{
	t_file	*file;

	file = (t_file*)item;
	if (file->opts->i)
		ft_printf("%ld ", (long)file->stats->st_ino);
	if (file->opts->l || file->opts->g)
		print_lgformat(file);
	ft_printf("%s\n", file->name);
}
