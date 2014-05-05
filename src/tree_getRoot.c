#include <TreePrivate.h>

// ############### Public Definitions ###############

Tree tree_getRoot(Tree node)
{
	if (!node)
	{
		return NULL;
	}
	
	while (node->parent)
	{
		node = node->parent;
	}
	
	return node;
}
