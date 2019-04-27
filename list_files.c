#include "ft_ls.h"

int				is_dot(char *name)
{
	if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (1);
	return (0);
}

int				permis_error(int error)
{
	if (error)
	{
		perror("ft_ls");
		errno = 0;
		return (1);
	}
	return (0);
}

void			lsdir(t_file *file)
{
	DIR				*fluxdir;
	t_file			*child_file;
	struct dirent	*dir;

	file->p_mw = (t_max*)malloc(sizeof(t_max));
	init_mw(file->p_mw);
	fluxdir = opendir(file->path);
	if (permis_error(errno))
		return ;
	while ((dir = readdir(fluxdir)))
	{
		if (file->opts->a || (!is_dot(dir->d_name) && (dir->d_name[0] != '.' || file->opts->cap_a)))
		{
			child_file = init_file(dir->d_name, file->path, file->opts);
			fill_mw(file->p_mw, child_file);
			bt_insert_item(&file->node, child_file, ft_cmp);
		}
	}
	bt_apply_infix(file->node, print_item);
	bt_free(&file->node, &freef);
	closedir(fluxdir);
}

void			lsr(void *arg)
{
	t_file		*file_dir;

	file_dir = (t_file*)arg;
	ft_printf("\n%s:\n", file_dir->path);
	ft_ls(arg);
}


void			lsdir_r(t_file *file)
{
	DIR				*fluxdir;
	t_file			*child_file;
	struct dirent	*dir;

	file->p_mw = (t_max*)malloc(sizeof(t_max));
	init_mw(file->p_mw);
	fluxdir = opendir(file->path);
	if (permis_error(errno))
		return ;
	while ((dir = readdir(fluxdir)))
	{
		if (file->opts->a || (!is_dot(dir->d_name) && (dir->d_name[0] != '.' || file->opts->cap_a)))
		{
			child_file = init_file(dir->d_name, file->path, file->opts);
			fill_mw(file->p_mw, child_file);
			if(dir->d_type == DT_DIR && !is_dot(dir->d_name))
			{
				child_file->p_mw = (t_max*)malloc(sizeof(t_max));
				bt_insert_item(&file->dirs, child_file, ft_cmp);
			}
			bt_insert_item(&file->node, child_file, ft_cmp);
		}
	}
	bt_apply_infix(file->node, print_item);
	if (file->dirs)
	{
		bt_apply_infix(file->dirs, lsr);
		free(file->dirs);                 //!!!!!!!!!!!!!!!!!!!!!!!!
	}
	bt_free(&file->node, &freef);
	closedir(fluxdir);
}

void		ft_ls(void *arg)
{
	t_file		*file_arg;

	file_arg = (t_file*)arg;
	errno = 0;
	if (S_ISDIR(file_arg->stats->st_mode))
			(file_arg->opts->cap_r) ? lsdir_r(file_arg)
									: lsdir(file_arg);
	else
		print_item((void*)file_arg);
}
