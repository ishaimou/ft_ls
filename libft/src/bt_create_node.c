#include "libft.h"

t_bt	*bt_create_node(void *item)
{
	t_bt	*node;

	if (!(node = (t_bt*)malloc(sizeof(t_bt))))
		return (NULL);
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
