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

static void	print_orglink(t_file *file)
{
	char	*org;

	if (is_large(file->opts) &&
		S_ISLNK(file->stats->st_mode))
	{
		ft_putstr(" -> ");
		org = ft_strnew(50);
		readlink(file->path, org, 50);
		ft_putstr(org);
		free(org);
	}
}

void		print_item(void *item)
{
	t_file	*file;
	char	*s1;
	char	*s2;

	file = (t_file*)item;
	s1 = (file->opts->p && S_ISDIR(file->stats->st_mode)) ? "/" : "";
	s2 = (file->opts->m) ? ", " : "\n";
	if (file->opts->i)
		ft_printf("%ld ", (long)file->stats->st_ino);
	if (is_large(file->opts))
		print_lgformat(file);
	ft_printf("%s%s", file->name, s1);
	print_orglink(file);
	ft_putstr((--file->mw->count) ? s2 : "\n");
}
