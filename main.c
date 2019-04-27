/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:47:50 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/27 15:04:57 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int ac, char **av)
{
	t_ls	ls;

	parse(ac, av, &ls);
	bt_apply_infix(ls.invtree, print_enoent);
	bt_apply_infix(ls.root, ft_ls);
	bt_free(&ls.invtree, &freef);
	bt_free(&ls.root, &freef);
	return (0);
}
