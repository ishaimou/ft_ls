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

t_file	*init_file(char *name, char *path, t_opt *opts)
{
	t_file		*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		exit(-1);
	file->name = ft_strdup(name);
	if (!*path)
		file->path = ft_strdup(file->name);
	file->opts = opts;
	if (!(file->stats = (struct stat*)malloc(sizeof(struct stat))))
		exit(-1);
	if (lstat(file->path, file->stats) == -1)
	{
		printf("STAT FAILED\n");
		free(file->stats);
		file->stats = NULL;
	}
	file->error = (!file->stats) ? errno : 0;
	return (file);
}

void	init_mw(t_ls *ls)
{
	ls->mw.count = 0;
	ls->mw.major = 0;
	ls->mw.minor = 0;
	ls->mw.size = 1;
	ls->mw.link = 1;
}
