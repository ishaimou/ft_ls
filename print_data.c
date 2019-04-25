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
	char	*org;
	char	*s;

	file = (t_file*)item;
	s = (file->opts->p && S_ISDIR(file->stats->st_mode)) ? "/" : "";
	if (file->opts->i)
		ft_printf("%ld ", (long)file->stats->st_ino);
	if (is_large(file->opts))
		print_lgformat(file);
	ft_printf("%s%s", file->name, s);
	if (S_ISLNK(file->stats->st_mode))
	{
		ft_putstr(" -> ");
		org = ft_strnew(50);
		readlink(file->path, org, 50);
		ft_printf("%s", org);
		free(org);
	}
	ft_putchar('\n');
}
