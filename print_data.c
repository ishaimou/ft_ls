#include "ft_ls.h"

static int	is_large(t_opt *opts)
{
	if (opts->l ||
		opts->n ||
		opts->o ||
		opts->g )
		return (1);
	return (0);
}

static void	print_orglink(t_file *file)
{
	char	*org;

	if (is_large(file->opts) &&
		S_ISLNK(file->stats->st_mode))
	{
		ft_putstr(" -> ");
		org = ft_strnew(50);
		readlink(file->path, org, 50);
		ft_putstr(org);
		free(org);
	}
}

char		*strdir(char *str)
{
	int		len;
	char	*strdir;

	len = ft_strlen(str) + 1;
	strdir = ft_strnew(len);
	ft_strcat(strdir, str);
	strdir[len - 1] = '/';
	return (strdir);
}

void		rcs_traversal(t_file *file)
{
	char			*tmp;
	t_max			*mw;
	t_file			*child_file;
	struct dirent	*dir;
	DIR				*fluxdir;

	fluxdir = opendir(file->path);
	ft_printf("\n%s/:\n", file->path);
	mw = (t_max*)malloc(sizeof(t_max));
	file->node = NULL;
	init_mw(mw);
	while ((dir = readdir(fluxdir)))
	{
		if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
		{
			tmp = ft_strjoin(strdir(file->name), dir->d_name);
			child_file = init_file(tmp, "", file->opts);
			fill_mw(child_file, mw);
			if (S_ISDIR(child_file->stats->st_mode))
				rcs_traversal(child_file);
			else
				bt_insert_item(&file->node, child_file, ft_cmp);
		}
	}
	if (mw->count)
	{
		bt_apply_infix(file->node, print_item);
		bt_free(&file->node, &freef);
	}
	else
		free(file->node);
	closedir(fluxdir);
}

void		print_item(void *item)
{
	t_file			*file;
	char			*s1;
	char			*s2;

	file = (t_file*)item;
	if (file->name[0] == '.' && !file->opts->a)
		return ;
	s1 = (file->opts->p && S_ISDIR(file->stats->st_mode)) ? "/" : "";
	s2 = (file->opts->m) ? ", " : "\n";
	if (file->opts->cap_r && S_ISDIR(file->stats->st_mode) &&
		ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
		rcs_traversal(file);
	else
	{
		if (file->opts->i)
			ft_printf("%ld ", (long)file->stats->st_ino);
		if (is_large(file->opts))
			print_lgformat(file);
		ft_printf("%s%s", file->name, s1);
			print_orglink(file);
		ft_putstr((--file->mw->count) ? s2 : "\n");
	}
}
