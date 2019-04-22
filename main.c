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
	ft_printf("ls: illegal option -- %c\n", c)
	ft_printf("usage: ls [-1lartiogmpnRSAG] [file ...]\n");
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

t_file	*init_file(char *name, char *path, struct stat *stats, t_bt *node)
{
	t_file	*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		error_malloc();
	file->name = name;
	file->path = path;
	file->stats = stats;
	file->node = node;
	return (file);
}

void	parse(int ac, char **av, t_ls *ls)
{
	struct stat	*stats;
	t_file		*file;
	int		i;

	i = 0;
	init_opts(&ls);
	while (++i < ac && av[i][0] == '-')
		add_opts(&ls, av[i]);
	while (i < ac)
	{
		if (!(stats = (struct stat*)malloc(sizeof(struct stat))))
			error_malloc();
		if (stat(av[i], stats) == -1)
			
		file = init_file(av[i], NULL, stats, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_ls	ls;

	parse(ac, av, &ls);
}
