#include <TreePrivate.h>



// ############### Public Definitions ###############

Tree tree_splayIndex(Tree root, int index)
{
	Tree node = tree_getByIndex(root, index);
	
	if (node)
	{
		if (tree_splay(node))
		{
			return NULL;
		}
		
		return node;
	}
	
	return NULL;
	
	
}



