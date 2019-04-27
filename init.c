#include "ft_ls.h"

void	init_opts(t_ls *ls)
{
	ls->opts.l = 0;
	ls->opts.a = 0;
	ls->opts.r = 0;
	ls->opts.t = 0;
	ls->opts.i = 0;
	ls->opts.o = 0;
	ls->opts.g = 0;
	ls->opts.m = 0;
	ls->opts.n = 0;
	ls->opts.p = 0;
	ls->opts.u = 0;
	ls->opts.cap_r = 0;
	ls->opts.cap_s = 0;
	ls->opts.cap_a = 0;
	ls->opts.cap_g = 0;
}

char		*set_path(t_file *file, char *path)
{
	char	*full_path;
	int		path_len;
	int		name_len;
	int		buff_len;

	if (!*path)
		return (ft_strdup(file->name));
	name_len = ft_strlen(file->name);
	path_len = ft_strlen(path);
	buff_len = name_len + path_len + 2;
	full_path = ft_strnew(name_len + path_len + 1);
	full_path = ft_strcpy(full_path, path);
	if (path[path_len - 1] != '/')
		ft_strlcat(full_path, "/", buff_len);
	ft_strlcat(full_path, file->name, buff_len);
	return (full_path);
}

t_opt 	*ft_options(t_opt *opts)
{
	t_opt	*new_opts;

	new_opts = (t_opt*)malloc(sizeof(t_opt));
	new_opts->l = opts->l;
	new_opts->a = opts->a;
	new_opts->r = opts->r;
	new_opts->t = opts->t;
	new_opts->i = opts->i;
	new_opts->o = opts->o;
	new_opts->g = opts->g;
	new_opts->m = opts->m;
	new_opts->n = opts->n;
	new_opts->p = opts->p;
	new_opts->u = opts->u;
	new_opts->cap_r = opts->cap_r;
	new_opts->cap_s = opts->cap_s;
	new_opts->cap_a = opts->cap_a;
	new_opts->cap_g = opts->cap_g;
	return (new_opts);
}

t_file	*init_file(char *name, char *path, t_opt *opts)
{
	t_file		*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		exit(-1);
	file->name = ft_strdup(name);
	file->path = set_path(file, path);
	//file->opts = ft_options(opts);
	file->opts = opts;
	file->node = NULL;
	file->dirs = NULL;
	if (!(file->stats = (struct stat*)malloc(sizeof(struct stat))))
		exit(-1);
	file->error = (lstat(file->path, file->stats) == -1) ? errno : 0;
	return (file);
}

void	init_mw(t_max *mw)
{
	mw->total = 0;
	mw->count = 0;
	mw->major = 0;
	mw->minor = 0;
	mw->size = 1;
	mw->link = 1;
	mw->own = 0;
	mw->grp = 0;
}
