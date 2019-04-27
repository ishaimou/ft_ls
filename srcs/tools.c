/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:19:27 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/27 16:45:16 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_dot(char *name)
{
	if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (1);
	return (0);
}

int		permis_error(int error)
{
	if (error)
	{
		perror("ft_ls");
		errno = 0;
		return (1);
	}
	return (0);
}

int		is_exec(t_file *file)
{
	if (S_ISREG(file->stats->st_mode) &&
		((S_IXUSR & file->stats->st_mode) ||
		(S_IXGRP & file->stats->st_mode) ||
		(S_IXOTH & file->stats->st_mode)))
		return (1);
	return (0);
}

int		is_large(t_opt *opts)
{
	if (opts->l || opts->n ||
		opts->o || opts->g)
		return (1);
	return (0);
}

int		is_special(mode_t mode)
{
	if (S_ISCHR(mode) ||
		S_ISBLK(mode) ||
		S_ISFIFO(mode) ||
		S_ISSOCK(mode))
		return (1);
	return (0);
}
