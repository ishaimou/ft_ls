#include "libft.h"

void	bt_insert_item(t_bt **root, void *item, int (*cmpf)(void *, void *))
{
	t_bt	*node;

	node = *root;
	if (!node)
		node = bt_create_node(item);
	else if (cmpf(item, node->item) < 0)
		bt_insert_item(&node->left, item, cmpf);
	else
		bt_insert_item(&node->right, item, cmpf);
	*root = node;
}
