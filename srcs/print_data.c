/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:41:42 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/27 16:42:58 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_orglink(t_file *file)
{
	char	*buff;

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

void		print_enoent(void *item)
{
	t_file	*file;

	file = (t_file*)item;
	ft_dprintf(2, "ft_ls: %s\n", strerror(file->error));
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
