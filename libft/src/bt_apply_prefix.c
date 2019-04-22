#include "libft.h"

void	bt_apply_prefix(t_bt *root, void (*applyf)(void *))
{
	if (root)
	{
		applyf(root->item);
		bt_apply_prefix(root->left, applyf);
		bt_apply_prefix(root->right, applyf);
	}
}
