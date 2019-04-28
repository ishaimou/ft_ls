/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:47:50 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/28 08:34:18 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_arg(void *item)
{
	t_file	*file;
	int		is_dir;

	file = (t_file*)item;
	is_dir = (S_ISDIR(file->stats->st_mode)) ? 1 : 0;
	if (!is_dir)
		(*(file->ac))++;
	if (*(file->ac) > 1 && is_dir)
		ft_printf("\n%s:\n", file->name);
	ft_ls(item);
}

int				main(int ac, char **av)
{
	t_ls	ls;

	parse(ac, av, &ls);
	bt_apply_infix(ls.invtree, print_enoent);
	bt_apply_infix(ls.root, ls_arg);
	bt_free(&ls.invtree, &freef);
	bt_free(&ls.root, &freef);
	return (0);
}
