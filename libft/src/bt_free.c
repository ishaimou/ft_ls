#include "libft.h"

void	bt_free(t_bt **root)
{
	t_bt *tmp;

	tmp = *root;
	if (!root)
		return ;
	if (tmp->left)
		bt_free(&tmp->left);
	if (tmp->right)
		bt_free(&tmp->right);
	free(tmp);
	*root = NULL;
}
