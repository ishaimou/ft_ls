#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "libft.h"

typedef struct		s_opt
{
	int		l:1;
	int		a:1:
	int		r:1;
	int		t:1;
	int		i:1;
	int		o:1;
	int		g:1;
	int		m:1;
	int		p:1;
	int		n:1;
	int		one:1;
	int		cap_a:1;
	int		cap_r:1;
	int		cap_s:1;
	int		cap_g:1;
}			t_opt;

typedef struct		s_file
{
	int		invalid:1;
	char		*name;
	char		*path;
	struct stat	*stats;
	t_bt		*node;
}			t_file;

typedef struct		s_ls
{
	t_opt		opt;
	t_file		file;
	t_bt		bt_arg;
}			t_ls;

#endif