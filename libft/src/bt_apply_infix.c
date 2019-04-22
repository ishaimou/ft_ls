#include "libft.h"

void	bt_apply_infix(t_bt *root, void (*applyf)(void *))
{
	if (root)
	{
		bt_apply_infix(root->left, applyf);
		applyf(root->item);
		bt_apply_infix(root->right, applyf);
	}
}
