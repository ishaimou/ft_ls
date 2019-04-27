/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:47:50 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/27 16:25:09 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		engine(void *item)
{
	t_file	*file;

	file = (t_file*)item;
	ft_ls(item);
	//if (file->c_mw->count > 1)
	//	ft_putchar('\n');
}

int			main(int ac, char **av)
{
	t_ls	ls;

	parse(ac, av, &ls);
	bt_apply_infix(ls.invtree, print_enoent);
	bt_apply_infix(ls.root, engine);
	bt_free(&ls.invtree, &freef);
	bt_free(&ls.root, &freef);
	return (0);
}
