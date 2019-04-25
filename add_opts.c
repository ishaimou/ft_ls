#include "ft_ls.h"

static void		ft_usage(char c)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", c);
	ft_dprintf(2, "usage: ls [-1lartuiogmpnRSAG] [file ...]\n");
	exit(-1);
}

static void		set_m(t_ls *ls)
{
	ls->opts.m = 1;
	ls->opts.l = 0;
	ls->opts.o = 0;
	ls->opts.g = 0;
	ls->opts.n = 0;
}

static void		set_no_m(t_ls *ls, char c)
{
	(c == 'l') ? ls->opts.l = 1 : 0;
	(c == 'o') ? ls->opts.o = 1 : 0;
	(c == 'g') ? ls->opts.g = 1 : 0;
	(c == 'n') ? ls->opts.n = 1 : 0;
	ls->opts.m = 0;
}

static void		set_t(t_ls *ls)
{
	ls->opts.t = 1;
	ls->opts.u = 0;
}

void			add_opts(t_ls *ls, char *s)
{
	while (*(++s))
	{
		if (!ft_strchr("1lartuiogmpnRSAG", *s))
			ft_usage(*s);
		(*s == 't') ? set_t(ls) : 0;
		(*s == 'm') ? set_m(ls) : 0;
		(*s == '1') ? ls->opts.l = 0 : 0;
		(*s == 'a') ? ls->opts.a = 1 : 0;
		(*s == 'r') ? ls->opts.r = 1 : 0;
		(*s == 'i') ? ls->opts.i = 1 : 0;
		(*s == 'p') ? ls->opts.p = 1 : 0;
		(*s == 'u') ? ls->opts.u = 1 : 0;
		(*s == 'R') ? ls->opts.cap_r = 1 : 0;
		(*s == 'S') ? ls->opts.cap_s = 1 : 0;
		(*s == 'A') ? ls->opts.cap_a = 1 : 0;
		(*s == 'G') ? ls->opts.cap_g = 1 : 0;
		(ft_strchr("lgon", *s)) ? set_no_m(ls, *s) : 0;
	}
}
