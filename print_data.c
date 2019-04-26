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
	char	*buff;
	int		size;

	if (is_large(file->opts) &&
		S_ISLNK(file->stats->st_mode))
	{
		ft_putstr(" -> ");
		buff = ft_strnew(BUFF_SIZE);
		readlink(file->path, buff, BUFF_SIZE);
		ft_putstr(buff);
		free(buff);
	}
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
	if (file->opts->i)
		ft_printf("%ld ", (long)file->stats->st_ino);
	if (is_large(file->opts))
		print_lgformat(file);
	(file->opts->cap_g) ? print_name(file, s1) :
						ft_printf("%s%s", file->name, s1);
	print_orglink(file);
			
	ft_putstr((--file->c_mw->count) ? s2 : "\n");
}
