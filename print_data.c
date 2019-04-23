#include "ft_ls.h"

static int	is_large(t_opt *opts)
{
	if (opts->l ||
		opts->n ||
		opts->o ||
		opts->g )
		return (1);
	return (0);
}

void		print_item(void *item)
{
	t_file	*file;
	char	*s;

	file = (t_file*)item;
	s = (file->opts->m && !file->is_last) ? ", " : "\n";
	if (file->opts->i)
		ft_printf("%ld ", (long)file->stats->st_ino);
	if (is_large(file->opts))
		print_lgformat(file);
	printf("%s%s", file->name, s);
}
