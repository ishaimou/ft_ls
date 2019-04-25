#include "ft_ls.h"
#include <sys/types.h>

static void		print_type(t_file *file)
{
	if (S_ISBLK(file->stats->st_mode))
		ft_putchar('b');
	else if (S_ISCHR(file->stats->st_mode))
		ft_putchar('c');
	else if (S_ISDIR(file->stats->st_mode))
		ft_putchar('d');
	else if (S_ISFIFO(file->stats->st_mode))
		ft_putchar('p');
	else if (S_ISLNK(file->stats->st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(file->stats->st_mode))
		ft_putchar('s');
	else if (S_ISREG(file->stats->st_mode))
		ft_putchar('-');
	else
		ft_putchar('-');
}

static void		print_modes(t_file *file)
{
	(file->stats->st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(file->stats->st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(file->stats->st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(file->stats->st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(file->stats->st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(file->stats->st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(file->stats->st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(file->stats->st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	if (file->stats->st_mode & S_ISVTX)
		ft_putchar('T');
	else
		(file->stats->st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
}

static void		print_amtime(t_file *file)
{
	char	*am_time;
	char	*year;
	char	*date;
//	char	*month;
//	char	*day;
	char	*str_time;
	int		tmp;

	if (file->opts->t)
		am_time = ctime(&file->stats->st_mtime);
	else
		am_time = ctime(&file->stats->st_atime);
	year = ft_strndup(am_time + 20, 4);
	//month = ft_strndup(am_time + 4, 3);
	//day = ft_strndup(am_time + 8, 2);
	date = ft_strndup(am_time + 4, 6);
	str_time = ft_strndup(am_time + 11, 5);
	ft_printf("%6s ", date);
	tmp = ABS(time(NULL) - ((file->opts->t) ?
			file->stats->st_mtime : file->stats->st_atime));
	ft_printf("%5s ", (tmp > 15552000) ? year : str_time);
	free(str_time);
	free(date);
	//free(day);
	//free(month);
	free(year);
}

int		is_special(mode_t mode)
{
	if (S_ISCHR(mode) ||
		S_ISBLK(mode) ||
		S_ISFIFO(mode) ||
		S_ISSOCK(mode))
		return (1);
	return (0);
}

void	print_aclxattr(t_file *file)
{
	acl_t	acl;

	acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
	if (listxattr(file->path, NULL, 0, XATTR_NOFOLLOW))
		ft_putchar('@');
	else if (acl)
	{
		ft_putchar('+');
		acl_free(acl);
	}
	else
		ft_putchar(' ');
}

void	print_maj_min(struct stat *stats)
{
	ft_printf("%u,", major(stats->st_rdev));
	ft_printf("%5u ", minor(stats->st_rdev));
}

void	print_lgformat(t_file *file)
{
	int		max_link = 2;
	int		max_size = 6;


	print_type(file);
	print_modes(file);
	print_aclxattr(file);
	ft_printf("  %*ld", max_link, (long)file->stats->st_nlink);
	if (!file->opts->g && !file->opts->n)
		ft_printf(" %s ", getpwuid(file->stats->st_uid)->pw_name);
	if (!file->opts->o && !file->opts->n)
		ft_printf(" %s ", getgrgid(file->stats->st_gid)->gr_name);
	if (file->opts->n && !file->opts->g)
		ft_printf("%ld  ", file->stats->st_uid);
	if (file->opts->n && !file->opts->o)
		ft_printf("%ld  ", file->stats->st_gid);
	if (is_special(file->stats->st_mode))
		print_maj_min(file->stats);
	else
		ft_printf("%*lld ", max_size, (long long)file->stats->st_size);
	print_amtime(file);
}
