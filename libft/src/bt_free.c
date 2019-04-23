#include "libft.h"

void	bt_free(t_bt **root, void (*freef)(void **))
{
	t_bt *tmp;

	tmp = *root;
	if (!*root)
		return ;
	if (tmp->left)
		bt_free(&tmp->left, freef);
	if (tmp->right)
		bt_free(&tmp->right, freef);
	freef(&tmp->item);
	free(tmp);
	*root = NULL;
}
