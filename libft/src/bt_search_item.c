#include "libft.h"

t_bt	*bt_search_item(t_bt *root, void *dataref, int (*cmpf)(void *, void *))
{
	if (!root || !cmpf(dataref, root->data))
		return (root);
	if (cmpf(dataref, root->data) < 0)
		return (bt_search_item(root->left, dataref, cmpf));
	return (bt_search_item(root->right, dataref, cmpf));
}