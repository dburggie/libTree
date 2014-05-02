#include <TreePrivate.h>



static Tree getNodeAtIndex(Tree tree, int index);

/* Gets the node at the given index.
 * Returns NULL if outside of range or error.
 * If negative index, gets node at (treesize + index) instead.
 */
Tree tree_getByIndex(Tree root, int index)
{
	
	if (!root) { return NULL; }
	
	//error case: index overflows tree
	if (index >= root->size || index + root->size < 0) { return NULL; }
	
	//negative index counts backwards from last node
	if (index < 0)
	{
		return getNodeAtIndex(root, root->size + index);
	}
	
	//return node using private recursive search function
	return getNodeAtIndex(root, index);
	
}


//private function

//recursively searches tree for the node at the given index
static Tree getNodeAtIndex(Tree tree, int index)
{
	
	if (!tree) { return NULL; }
	
	else if (index < tree->sizeLeft)
	{
		//index is in left sub-tree
		return getNodeAtIndex(tree->leftTree, index);
	}
	
	else if (index > tree->sizeLeft)
	{
		//node is in right sub-tree, decrement index by left tree size
		return getNodeAtIndex( tree->rightTree, (index - 1 - tree->sizeLeft) );
	}
	
	else
	{
		//index is not to left or right, is thus at this node.
		return tree;
	}
	
}
