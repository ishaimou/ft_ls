#include "libft.h"

int		bt_size_count(t_bt *root)
{
	if (!root)
		return (0);
	else
		return (1 + bt_size_count(root->left) + bt_size_count(root->right));
}
