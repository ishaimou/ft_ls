#include "ft_ls.h"

static int	is_large(t_opt *opts)
{
	if (opts->l || opts->n ||
		opts->o || opts->g )
		return (1);
	return (0);
}

static void	print_orglink(t_file *file)
{
	char	*org;
	int		size;

	if (is_large(file->opts) &&
		S_ISLNK(file->stats->st_mode))
	{
		size = file->stats->st_size;
		ft_putstr(" -> ");
		org = ft_strnew(size);
		readlink(file->path, org, size + 1);
		ft_putstr(org);
		free(org);
	}
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

void		rcs_traversal(t_file *file)
{
	t_max			*mw;
	t_file			*child_file;
	struct dirent	*dir;
	DIR				*fluxdir;

	fluxdir = opendir(file->path);
	if (errno_msg(errno))
		return ;
	if (file->mw->count > 1)
		ft_printf("\n%s:\n", file->path);
	mw = (t_max*)malloc(sizeof(t_max));
	init_mw(mw);
	while ((dir = readdir(fluxdir)))
	{
		if (dir->d_name[0] != '.' || file->opts->a ||
			(file->opts->cap_a && ft_strcmp(dir->d_name, ".") &&
			ft_strcmp(dir->d_name, "..")))
		{
			child_file = init_file(dir->d_name, file->path, file->opts);
			fill_mw(child_file, mw);
			if (file->opts->cap_r && S_ISDIR(child_file->stats->st_mode) && ft_strcmp(child_file->name, "."))
				rcs_traversal(child_file);
			else
				bt_insert_item(&file->node, child_file, ft_cmp);
		}
	}
	if (mw->count)
	{
		bt_apply_infix(file->node, (file->opts->cap_r) ?
				print_item : print_lvl1);
		bt_free(&file->node, &freef);
	}
	free(mw);
	closedir(fluxdir);
}

static int	is_exec(t_file *file)
{
	if (S_ISREG(file->stats->st_mode) && (
		(S_IXUSR & file->stats->st_mode) ||
		(S_IXGRP & file->stats->st_mode) ||
		(S_IXOTH & file->stats->st_mode)))
		return (1);
	return (0);
}

void		print_name(t_file *file, char *suffix)
{
	if (is_exec(file))
		ft_printf("%{PURPLE}%s%s%{eoc}", file->name, suffix);
	else if (S_ISREG(file->stats->st_mode))
		ft_printf("%s%s", file->name, suffix);
	else if (S_ISDIR(file->stats->st_mode))
		ft_printf("%{CYAN}%s%s%{eoc}", file->name, suffix);
	else if (S_ISCHR(file->stats->st_mode))
		ft_printf("%{BLUE}%s%s%{eoc}", file->name, suffix);
	else if (S_ISBLK(file->stats->st_mode))
		ft_printf("%{blue}%s%s%{eoc}", file->name, suffix);
	else if (S_ISFIFO(file->stats->st_mode))
		ft_printf("%{yellow}%s%s%{eoc}", file->name, suffix);
	else if (S_ISLNK(file->stats->st_mode))
		ft_printf("%{red}%s%s%{eoc}", file->name, suffix);
	else if (S_ISSOCK(file->stats->st_mode))
		ft_printf("%{green}%s%s%{eoc}", file->name, suffix);
}

void		print_item(void *item)
{
	t_file			*file;
	char			*s1;
	char			*s2;

	file = (t_file*)item;
	s1 = (file->opts->p && S_ISDIR(file->stats->st_mode)) ? "/" : "";
	s2 = (file->opts->m) ? ", " : "\n";
	if (S_ISDIR(file->stats->st_mode))
		rcs_traversal(file);
	else
	{
		if (file->opts->i)
			ft_printf("%ld ", (long)file->stats->st_ino);
		if (is_large(file->opts))
			print_lgformat(file);
		(file->opts->cap_g) ? print_name(file, s1) :
							ft_printf("%s%s", file->name, s1);
		print_orglink(file);
		ft_putstr((--file->mw->count) ? s2 : "\n");
	}
}

void		print_lvl1(void *item)
{
	t_file			*file;
	char			*s1;
	char			*s2;

	file = (t_file*)item;
	s1 = (file->opts->p && S_ISDIR(file->stats->st_mode)) ? "/" : "";
	s2 = (file->opts->m) ? ", " : "\n";
	if (file->opts->i)
		ft_printf("%ld ", (long)file->stats->st_ino);
	if (is_large(file->opts))
		print_lgformat(file);
	(file->opts->cap_g) ? print_name(file, s1) :
						ft_printf("%s%s", file->name, s1);
	print_orglink(file);
	ft_putstr((--file->mw->count) ? s2 : "\n");
}
