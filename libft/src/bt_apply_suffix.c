#include "libft.h"

void	bt_apply_suffix(t_bt *root, void (*applyf)(void *))
{
	if (root)
	{
		bt_apply_prefix(root->left, applyf);
		bt_apply_prefix(root->right, applyf);
		applyf(root->item);
	}
}
