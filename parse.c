#include "ft_ls.h"

static int	 parse_default(int i, int ac, t_ls *ls)
{
	t_file	*file;

	if (i == ac)
	{	
		file = init_file(".", "", &ls->opts);
		fill_mw(&ls->mw, file);
		bt_insert_item(&ls->root, file, ft_cmp);
		return (1);
	}
	return (0);
}

void		parse(int ac, char **av, t_ls *ls)
{
	struct stat	*stats;
	t_file		*file;
	int		i;

	i = 1;
	init_opts(ls);
	init_mw(&ls->mw);
	while (i < ac && av[i][0] == '-')
		add_opts(ls, av[i++]);
	if (parse_default(i, ac, ls))
		return ;
	while (i < ac)
	{
		file = init_file(av[i++], "", &ls->opts);
		if (file->error)
			bt_insert_item(&ls->invtree, file, ft_cmp_enoent);
		else
		{
			fill_mw(&ls->mw, file);
			bt_insert_item(&ls->root, file, ft_cmp);
		}		
	}
}
