/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lfomat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:08:05 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/27 16:39:37 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_amtime(t_file *file)
{
	char	*am_time;
	char	*year;
	char	*date;
	char	*str_time;
	int		tmp;

	if (file->opts->u)
		am_time = ctime(&file->stats->st_atime);
	else
		am_time = ctime(&file->stats->st_mtime);
	year = ft_strndup(am_time + 20, 4);
	date = ft_strndup(am_time + 4, 6);
	str_time = ft_strndup(am_time + 11, 5);
	ft_printf("%6s ", date);
	tmp = ABS(time(NULL) - ((file->opts->u) ?
			file->stats->st_atime : file->stats->st_mtime));
	ft_printf("%5s ", (tmp > 15552000) ? year : str_time);
	free(str_time);
	free(date);
	free(year);
}

static void		print_maj_min(t_file *file)
{
	ft_printf("   %*u, ", file->c_mw->major, major(file->stats->st_rdev));
	ft_printf("%*u ", file->c_mw->minor - 3, minor(file->stats->st_rdev));
}

static void		print_grp_own(t_file *file)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(file->stats->st_uid);
	grp = getgrgid(file->stats->st_gid);
	if (!file->opts->g && !file->opts->n)
	{
		(pwd) ? ft_printf(" %-*s ", file->c_mw->own, pwd->pw_name)
			: ft_printf(" %-*d ", file->c_mw->own, file->stats->st_uid);
	}
	if (!file->opts->o && !file->opts->n)
	{
		(grp) ? ft_printf(" %-*s ", file->c_mw->grp, grp->gr_name)
			: ft_printf(" %-*d ", file->c_mw->grp, file->stats->st_gid);
	}
	if (file->opts->n && !file->opts->g)
		ft_printf("%-*ld ", file->c_mw->nown, file->stats->st_uid);
	if (file->opts->n && !file->opts->o)
		ft_printf("%-*ld ", file->c_mw->ngrp, file->stats->st_gid);
}

void			print_lgformat(t_file *file)
{
	if (file->c_mw->total)
	{
		ft_printf("total %d\n", file->c_mw->total);
		file->c_mw->total = 0;
	}
	print_modes(file);
	ft_printf(" %*ld", file->c_mw->link, (long)file->stats->st_nlink);
	print_grp_own(file);
	if (is_special(file->stats->st_mode))
		print_maj_min(file);
	else
		ft_printf(" %*lld ", file->c_mw->size,
				(long long)file->stats->st_size);
	print_amtime(file);
}