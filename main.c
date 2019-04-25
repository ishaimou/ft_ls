#include "ft_ls.h"

void		fill_mw(t_file *file, t_max *mw)
{
	struct group	*grp;
	struct passwd	*own;

	file->mw = mw;
	mw->count++;
	grp = getgrgid(file->stats->st_gid);
	own = getpwuid(file->stats->st_uid);
	mw->grp = ft_max(mw->grp, ft_strlen(grp->gr_name));
	mw->own = ft_max(mw->own, ft_strlen(own->pw_name));
	mw->ngrp = ft_max(mw->ngrp, ft_intlen(file->stats->st_gid));
	mw->nown = ft_max(mw->ngrp, ft_intlen(file->stats->st_uid));
	mw->size = ft_max(mw->size, ft_intlen(file->stats->st_size));
	mw->link = ft_max(mw->size, ft_intlen(file->stats->st_nlink));
	mw->major = ft_max(mw->size, ft_intlen(major(file->stats->st_dev)));
	mw->minor = ft_max(mw->size, ft_intlen(minor(file->stats->st_dev)));
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
	if (i == ac)
	{
		file = init_file(".", "", &ls->opts);
		fill_mw(file, &ls->mw);
		bt_insert_item(&ls->root, file, ft_cmp);
		return ;
	}
	while (i < ac)
	{
		file = init_file(av[i++], "", &ls->opts);
		fill_mw(file, &ls->mw);
		bt_insert_item(&ls->root, file, ft_cmp);
	}
}

int			main(int ac, char **av)
{
	t_ls	ls;
	t_file	*file;

	parse(ac, av, &ls);
	bt_apply_infix(ls.root, print_item);
	//printf("size: %d\n", bt_size_count(ls.root));
	//printf("level: %d\n", bt_level_count(ls.root));
	bt_free(&ls.root, &freef);
	return (0);
}
