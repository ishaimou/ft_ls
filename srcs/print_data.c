/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:41:42 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/28 10:31:02 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_orglink(t_file *file)
{
	char	*buff;

	if (is_large(file->opts) &&
		S_ISLNK(file->stats->st_mode))
	{
		write(1, " -> ", 4);
		buff = ft_strnew(BUFF_SIZE);
		readlink(file->path, buff, BUFF_SIZE);
		ft_putstr(buff);
		free(buff);
	}
}

void		print_enoent(void *item)
{
	t_file	*file;

	file = (t_file*)item;
	write(2, "ft_ls: ", 7);
	ft_putstr_fd(file->name, 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(file->error), 2);
	write(2, "\n", 1);
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

int			print_column(t_file *file, char *s1)
{
	char		*s2;

	if (file->opts->c)
	{
		s2 = (--file->c_mw->count % 3 == 0) ? "\n" : "";
		ft_printf("%-20s", file->name);
		ft_putstr(s1);
		ft_putstr(s2);
		return (1);
	}
	return (0);
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
	if (print_column(file, s1))
		return ;
	if (file->opts->cap_g)
		print_name(file, s1);
	else
	{
		ft_putstr(file->name);
		ft_putstr(s1);
	}
	print_orglink(file);
	ft_putstr((--file->c_mw->count) ? s2 : "\n");
}
