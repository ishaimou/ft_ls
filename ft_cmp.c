/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:59:00 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/27 14:59:34 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_cmp_size(t_file *f1, t_file *f2)
{
	if (f1->stats->st_size == f2->stats->st_size)
		return (ft_strcmp(f1->name, f2->name));
	return (f1->stats->st_size < f2->stats->st_size ? 1 : -1);
}

static int	ft_cmp_time(t_file *f1, t_file *f2)
{
	if (f1->opts->t)
	{
		if (f1->stats->st_mtime == f2->stats->st_mtime)
			return (ft_strcmp(f1->name, f2->name));
		return (f1->stats->st_mtime < f2->stats->st_mtime ? 1 : -1);
	}
	else
	{
		if (f1->stats->st_atime == f2->stats->st_atime)
			return (ft_strcmp(f1->name, f2->name));
		return (f1->stats->st_atime < f2->stats->st_atime ? 1 : -1);
	}
}

int			pure_dir(t_file *f)
{
	if (S_ISDIR(f->stats->st_mode)
			&& ft_strcmp(f->name, ".")
			&& ft_strcmp(f->name, ".."))
		return (1);
	return (0);
}

int			ft_cmp_enoent(void *item1, void *item2)
{
	t_file	*f1;
	t_file	*f2;

	f1 = (t_file*)item1;
	f2 = (t_file*)item2;
	return (ft_strcmp(f1->name, f2->name));
}

int			ft_cmp(void *item1, void *item2)
{
	t_file	*f1;
	t_file	*f2;
	int		rev;
	int		ret;

	f1 = (t_file*)item1;
	f2 = (t_file*)item2;
	rev = (f1->opts->r) ? -1 : 1;
	if (pure_dir(f1) && !pure_dir(f2) && f1->opts->cap_r)
		return (rev);
	if (pure_dir(f2) && !pure_dir(f1) && f1->opts->cap_r)
		return (-rev);
	if (f1->opts->cap_s)
		ret = ft_cmp_size(f1, f2);
	else if (f1->opts->t)
		ret = ft_cmp_time(f1, f2);
	else
		ret = ft_strcmp(f1->name, f2->name);
	return (ret * rev);
}
