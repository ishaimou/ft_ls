/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:16:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/27 20:09:25 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			lsdir(t_file *file, DIR *fluxdir)
{
	t_file			*child_file;
	struct dirent	*dir;

	while ((dir = readdir(fluxdir)))
	{
		if (file->opts->a || (!is_dot(dir->d_name) &&
					(dir->d_name[0] != '.' || file->opts->cap_a)))
		{
			child_file = init_file(dir->d_name, file->path, file->opts);
			fill_mw(file->p_mw, child_file);
			bt_insert_item(&file->node, child_file, ft_cmp);
		}
	}
	bt_apply_infix(file->node, print_item);
	bt_free(&file->node, &freef);
}

static void			lsr(void *arg)
{
	t_file			*file_dir;

	file_dir = (t_file*)arg;
	free(file_dir->p_mw);
	file_dir->p_mw = NULL;
	ft_printf("\n%s:\n", file_dir->path);
	ft_ls(arg);
}

static void			lsdir_r(t_file *file, DIR *fluxdir)
{
	t_file			*child_file;
	struct dirent	*dir;

	while ((dir = readdir(fluxdir)))
		if (file->opts->a || (!is_dot(dir->d_name) &&
					(dir->d_name[0] != '.' || file->opts->cap_a)))
		{
			child_file = init_file(dir->d_name, file->path, file->opts);
			fill_mw(file->p_mw, child_file);
			if (dir->d_type == DT_DIR && !is_dot(dir->d_name))
			{
				child_file->p_mw = (t_max*)malloc(sizeof(t_max));
				bt_insert_item(&file->dirs, child_file, ft_cmp);
			}
			bt_insert_item(&file->node, child_file, ft_cmp);
		}
	bt_apply_infix(file->node, print_item);
	if (file->dirs)
		bt_apply_infix(file->dirs, lsr);
	bt_free(&file->node, &freef);
	bt_free_tree(&file->dirs);
}

void				ft_ls(void *arg)
{
	t_file			*file_arg;
	DIR				*fluxdir;

	file_arg = (t_file*)arg;
	errno = 0;
	if (S_ISDIR(file_arg->stats->st_mode))
	{
		if (file_arg->c_mw->total != -1 && is_large(file_arg->opts))
		{
			ft_printf("total %d\n", file_arg->c_mw->total);
			file_arg->c_mw->total = -1;
		}
		fluxdir = opendir(file_arg->path);
		if (permis_error(errno))
			return ;
		file_arg->p_mw = (t_max*)malloc(sizeof(t_max));
		init_mw(file_arg->p_mw);
		(file_arg->opts->cap_r) ? lsdir_r(file_arg, fluxdir)
			: lsdir(file_arg, fluxdir);
		closedir(fluxdir);
	}
	else
		print_item((void*)file_arg);
}
