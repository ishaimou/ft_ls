/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:16:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/28 22:06:25 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			total_rmz(t_file *file)
{
	if (is_large(file->opts) && file->c_mw->total != -1)
	{
		write(1, "total ", 6);
		ft_putnbr(file->c_mw->total);
		write(1, "\n", 1);
		file->c_mw->total = -1;
	}
}

static void			lsdir(t_file *file, DIR *fluxdir)
{
	t_file			*child_file;
	struct dirent	*dir;

	child_file = NULL;
	while ((dir = readdir(fluxdir)))
		if (file->opts->a || (!is_dot(dir->d_name) &&
					(dir->d_name[0] != '.' || file->opts->cap_a)))
		{
			child_file = init_file(dir->d_name, file->path, file->opts);
			fill_mw(file->p_mw, child_file);
			bt_insert_item(&file->node, child_file, ft_cmp);
		}
	if (child_file)
		total_rmz(child_file);
	bt_apply_infix(file->node, print_item);
	bt_free(&file->node, &freef);
}

static void			lsr(void *arg)
{
	t_file			*file_dir;

	file_dir = (t_file*)arg;
	ft_printf("\n%s:\n", file_dir->path);
	total_rmz(file_dir);
	free(file_dir->p_mw);
	file_dir->p_mw = NULL;
	ft_ls(arg);
}

static void			lsdir_r(t_file *file, DIR *fluxdir)
{
	t_file			*child_file;
	struct dirent	*dir;

	child_file = NULL;
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
	if (child_file)
		total_rmz(child_file);
	bt_apply_infix(file->node, print_item);
	if (file->dirs)
		bt_apply_infix(file->dirs, lsr);
	bt_free(&file->node, &freef);
	bt_free_tree(&file->dirs);
}

void				ft_ls(void *arg)
{
	t_file			*file;
	DIR				*fluxdir;

	file = (t_file*)arg;
	errno = 0;
	if (S_ISDIR(file->stats->st_mode))
	{
		if (!(file->stats->st_mode & S_IXUSR))
			return ;
		fluxdir = opendir(file->path);
		if (permis_error(file->name, errno))
			return ;
		file->p_mw = (t_max*)malloc(sizeof(t_max));
		init_mw(file->p_mw);
		(file->opts->cap_r) ? lsdir_r(file, fluxdir)
			: lsdir(file, fluxdir);
		closedir(fluxdir);
	}
	else
		print_item((void*)file);
}
