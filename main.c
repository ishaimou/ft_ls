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
	ft_dprintf(2, "ls: illegal option -- %c\n", c);
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

void	error_malloc(void)
{
	perror("malloc: not enough space");
	exit(-1);
}

t_file	*init_file(char *name, char *path, t_opt *opts)
{
	t_file		*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		error_malloc();
	file->name = ft_strdup(name);
	if (!*path)
		file->path = ft_strdup(file->name);
	file->opts = opts;
	if (!(file->stats = (struct stat*)malloc(sizeof(struct stat))))
		error_malloc();
	if (stat(file->path, file->stats) == -1)
	{
		printf("STAT FAILED\n");
		free(file->stats);
		file->stats = NULL;
	}
	file->error = (!file->stats) ? errno : 0;
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
	if (f1->stats->st_mtime == f2->stats->st_mtime)
		return (ft_strcmp(f1->name, f2->name));
	return (f1->stats->st_mtime < f2->stats->st_mtime ? -1 : 1);
}

int	ft_cmp(void* item1, void *item2)
{
	t_file	*f1;
	t_file	*f2;
	int		rev;
	int		ret;
	
	f1 = (t_file*)item1;
	f2 = (t_file*)item2;
	if (f1->opts->cap_s)
		ret = ft_cmp_size(f1, f2);
	if (f1->opts->t && !f1->opts->cap_s)
		ret = ft_cmp_time(f1, f2);
	ret = ft_strcmp(f1->name, f2->name);
	rev = (f1->opts->r) ? -1 : 1;
	return (ret * rev);
}

void	parse(int ac, char **av, t_ls *ls)
{
	struct stat	*stats;
	t_file		*file;
	int		i;

	i = 1;
	init_opts(ls);
	while (i < ac && av[i][0] == '-')
		add_opts(ls, av[i++]);
	while (i < ac)
	{
		file = init_file(av[i++], "", &ls->opts);
		bt_insert_item(&ls->root, file, ft_cmp);
	}
}

int	main(int ac, char **av)
{
	t_ls	ls;

	parse(ac, av, &ls);
	bt_apply_infix(ls.root, print_item);
	printf("size: %d\n", bt_size_count(ls.root));
	printf("level: %d\n", bt_level_count(ls.root));
	bt_free(&ls.root, &freef);
	return (0);
}
