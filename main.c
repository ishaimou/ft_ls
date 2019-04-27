#include "ft_ls.h"

void		fill_mw(t_max *p_mw, t_file *file)
{
	struct group	*grp;
	struct passwd	*own;

	file->c_mw = p_mw;
	p_mw->count++;
	p_mw->total += file->stats->st_blocks;
	if ((grp = getgrgid(file->stats->st_gid)))
		p_mw->grp = ft_max(p_mw->grp, ft_strlen(grp->gr_name));
	if ((own = getpwuid(file->stats->st_uid)))
		p_mw->own = ft_max(p_mw->own, ft_strlen(own->pw_name));
	p_mw->ngrp = ft_max(p_mw->ngrp, ft_intlen(file->stats->st_gid));
	p_mw->nown = ft_max(p_mw->nown, ft_intlen(file->stats->st_uid));
	p_mw->size = ft_max(p_mw->size, ft_intlen(file->stats->st_size));
	p_mw->link = ft_max(p_mw->link, ft_intlen(file->stats->st_nlink));
	p_mw->major = ft_max(p_mw->major, ft_intlen(major(file->stats->st_dev)));
	p_mw->minor = ft_max(p_mw->minor, ft_intlen(minor(file->stats->st_dev)));
}

int			main(int ac, char **av)
{
	t_ls	ls;
	t_file	*file;

	init_mw(&ls.mw);
	parse(ac, av, &ls);
	bt_apply_infix(ls.invtree, print_enoent);
	bt_apply_infix(ls.root, ft_ls);
	bt_free(&ls.invtree, &freef);
	bt_free(&ls.root, &freef);
	return (0);
}
