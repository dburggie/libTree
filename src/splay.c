#include <TreePrivate.h>



// ############### Public Definitions ###############

int tree_splay(Tree node)
{
	if (!node) { return 1; }
	
	//is our node already the root node?
	if (node->gender == ROOT) { return 0; }
	
	 //this shouldn't ever be null, but safety first
	if (!node->parent) { return 1; }
	
	//swap with parent, taking handedness into account
	while (node->gender != ROOT)
	{
		tree_rotate(node);
	}
	
	return 0;
}



