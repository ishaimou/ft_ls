/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:19:27 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/28 11:16:13 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_dot(char *name)
{
	if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (1);
	return (0);
}

/*int		permis_error(int error)
  {
  if (error)
  {
  perror("ft_ls");
  errno = 0;
  return (1);
  }
  return (0);
  }
  */
int		permis_error(char *name, int error)
{
	if (error)
	{
		write(2, "ft_ls: ", 7);
		ft_putstr_fd(name, 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(error), 2);
		write(2, "\n", 1);
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
