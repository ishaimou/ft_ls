#include "ft_ls.h"

void		fill_mw(t_max *p_mw, t_file *file)
{
	struct group	*grp;
	struct passwd	*own;

	file->c_mw = p_mw;
	p_mw->count++;
	p_mw->total += file->stats->st_blocks;
	grp = getgrgid(file->stats->st_gid);
	own = getpwuid(file->stats->st_uid);
	p_mw->grp = ft_max(p_mw->grp, ft_strlen(grp->gr_name));
	p_mw->own = ft_max(p_mw->own, ft_strlen(own->pw_name));
	p_mw->ngrp = ft_max(p_mw->ngrp, ft_intlen(file->stats->st_gid));
	p_mw->nown = ft_max(p_mw->nown, ft_intlen(file->stats->st_uid));
	p_mw->size = ft_max(p_mw->size, ft_intlen(file->stats->st_size));
	p_mw->link = ft_max(p_mw->link, ft_intlen(file->stats->st_nlink));
	p_mw->major = ft_max(p_mw->major, ft_intlen(major(file->stats->st_dev)));
	p_mw->minor = ft_max(p_mw->minor, ft_intlen(minor(file->stats->st_dev)));
}

int			ft_cmp_enoent(void *item1, void *item2)
{
	t_file	*f1;
	t_file	*f2;

	f1 = (t_file*)item1;
	f2 = (t_file*)item2;
	return (ft_strcmp(f1->name, f2->name));
}

int	 parse_default(int i, int ac, t_ls *ls)
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
		fill_mw(&ls->mw, file);
		if (file->error == ENOENT)
			bt_insert_item(&ls->invtree, file, ft_cmp_enoent);
		else
			bt_insert_item(&ls->root, file, ft_cmp);
	}
}

void		print_enoent(void *item)
{
	t_file	*file;

	file = (t_file*)item;
	ft_dprintf(2, "ft_ls: %s: No such file or directory\n", file->name);
}

int			errno_msg(int error)
{
	if (error)
	{
		if (error == 13)
			ft_dprintf(2, "ft_ls: Permission denied\n");
		else if (error == ELOOP)
			ft_dprintf(2, "ft_ls: Lot of symbolic links\n");
		else if (error == EFAULT)
			ft_dprintf(2, "ft_ls: Invalid Address\n");
		else if (error == ENAMETOOLONG)
			ft_dprintf(2, "ft_ls: Long Name\n");
		return (1);
	}
	return (0);
}

void			ft_ls(void *arg);

void			lsdir(t_file *file)
{
	DIR				*fluxdir;
	t_file			*child_file;
	struct dirent	*dir;

	file->p_mw = (t_max*)malloc(sizeof(t_max));
	init_mw(file->p_mw);
	fluxdir = opendir(file->path);
	if (errno_msg(errno))
		return ;
	while ((dir = readdir(fluxdir)))
	{
		if (dir->d_name[0] != '.')
		{
			child_file = init_file(dir->d_name, file->path, file->opts);
			fill_mw(file->p_mw, child_file);
			bt_insert_item(&file->node, child_file, ft_cmp);
		}
	}
	bt_apply_infix(file->node, print_item);
	bt_free(&file->node, &freef);
	closedir(fluxdir);
}

void			lsr(void *arg)
{
	t_file		*file_dir;

	file_dir = (t_file*)arg;
	ft_printf("\n%s:\n", file_dir->path);
	ft_ls(arg);
}

void			lsdir_r(t_file *file)
{
	DIR				*fluxdir;
	t_file			*child_file;
	struct dirent	*dir;
	struct dirent	*dir2;
	t_max			*mw;

	file->p_mw = (t_max*)malloc(sizeof(t_max));
	init_mw(file->p_mw);
	fluxdir = opendir(file->path);
	if (errno_msg(errno))
		return ;
	while ((dir = readdir(fluxdir)))
	{
		if (dir->d_name[0] != '.')
		{
			child_file = init_file(dir->d_name, file->path, file->opts);
			fill_mw(file->p_mw, child_file);
			if(dir->d_type == DT_DIR)
			{
				child_file->p_mw = (t_max*)malloc(sizeof(t_max));
				bt_insert_item(&file->dirs, child_file, ft_cmp);
			}
			bt_insert_item(&file->node, child_file, ft_cmp);
		}
	}
	bt_apply_infix(file->node, print_item);
	bt_apply_infix(file->dirs, lsr);
	bt_free(&file->node, &freef);
	//bt_free(&file->dirs, &freef);
	closedir(fluxdir);
	/*fluxdir = opendir(file->path);
	while ((dir2 = readdir(fluxdir)))
	{
		if (dir2->d_name[0] != '.' && dir2->d_type == DT_DIR)
		{
			child_file = init_file(dir2->d_name, file->path, file->opts);
			fill_mw(file->p_mw, child_file);
			ft_printf("\nrecursive: %s:\n", dir2->d_name);
			ft_ls(child_file);
		}
	}
	closedir(fluxdir);*/
}

void		ft_ls(void *arg)
{
	t_file		*file_arg;

	file_arg = (t_file*)arg;
	if (S_ISDIR(file_arg->stats->st_mode))
	{
		//if (file_arg->opts->a)
		//	lsdir_a(file_arg);
		//else if (file_arg->opts->cap_a)
		//	lsdir_cap_a(file_arg);
		//else
			(file_arg->opts->cap_r) ? lsdir_r(file_arg) : lsdir(file_arg);
	}
	else
		print_item((void*)file_arg);
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
