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
	ls->opts.cap_r = 0;
	ls->opts.cap_s = 0;
	ls->opts.cap_a = 0;
	ls->opts.cap_g = 0;
}

void	ft_usage(char c)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", c)
	ft_dprintf(2, "usage: ls [-1lartiogmpnRSAG] [file ...]\n");
	exit(-1);
}

void	add_opts(t_ls *ls, char *s)
{
	while (*(++s))
	{
		if (!ft_strchr("1lartiogmpnRSAG", *s))
			ft_usage(*s);
		(*s == '1') ? ls->opts.l = 0 : 0;
		(*s == 'l') ? ls->opts.l = 1 : 0;
		(*s == 'a') ? ls->opts.a = 1 : 0;
		(*s == 'r') ? ls->opts.r = 1 : 0;
		(*s == 't') ? ls->opts.t = 1 : 0;
		(*s == 'i') ? ls->opts.i = 1 : 0;
		(*s == 'o') ? ls->opts.o = 1 : 0;
		(*s == 'g') ? ls->opts.g = 1 : 0;
		(*s == 'm') ? ls->opts.m = 1 : 0;
		(*s == 'p') ? ls->opts.p = 1 : 0;
		(*s == 'n') ? ls->opts.n = 1 : 0;
		(*s == 'R') ? ls->opts.cap_r = 1 : 0;
		(*s == 'S') ? ls->opts.cap_s = 1 : 0;
		(*s == 'A') ? ls->opts.cap_a = 1 : 0;
		(*s == 'G') ? ls->opts.cap_g = 1 : 0;
	}
}

void	error_mallloc(void)
{
	perror("malloc: not enough space");
	exit(-1);
}

t_file	*init_file(char *name, char *path, t_opt *opts)
{
	t_file		*file;
	struct stat	*stats;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		error_malloc();
	if (!(stats = (struct stat*)malloc(sizeof(struct stat))))
		error_malloc();
	if (stat(name, stats) == -1)
		stats = NULL;
	file->error = (!stats) ? errno : 0;
	file->name = ft_strdup(name);
	file->path = ft_strdup(path);
	file->stats = stats;
	file->opts = opts;
	return (file);
}

int	ft_cmp_size(t_file *f1, t_file *f2)
{
	if (f1->stats->st_size == f2->stats->st_size)
		return (ft_strcmp(f1->name, f2->name));
	return (f1->stats->st_size < f2->stats->st_size ? -1 : 1);
}

int	ft_cmp_time(t_file *f1, t_file *f2)
{
	if (f1->stats->st_time == f2->stats->st_time)
		return (ft_strcmp(f1->name, f2->name));
	return (f1->stats->st_atime < f2->stats->st_atime ? -1 : 1);
}

int	ft_cmp(void* data1, void *data2)
{
	t_file	f1;
	t_file	f2;

	f1 = (t_file*)data1;
	f2 = (t_file*)data2;
	if (f1->opts.cap_s)
		return (ft_cmp_size(f1, f2) * -(f1->opts.r));
	if (f1->opts.t)
		return (ft_cmp_time(f1, f2) * -(f1->opts.r));
	return (ft_strcmp(f1->name, f2->name) * -(f1->opts.r));
}

void	parse(int ac, char **av, t_ls *ls)
{
	struct stat	*stats;
	t_file		*file;
	int		i;

	i = 0;
	file->error = 0;
	init_opts(&ls);
	while (++i < ac && av[i][0] == '-')
		add_opts(&ls, av[i]);
	while (i < ac)
	{
		file = init_file(av[i++], "", ls->opts);
		bt_insert_item(ls->root, file, ft_cmp);
	}
}

int	main(int ac, char **av)
{
	t_ls	ls;

	parse(ac, av, &ls);
}
