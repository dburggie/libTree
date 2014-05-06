#include <TreePrivate.h>

// ############### Private Declarations ###############

static Tree getCentralNode(Tree root);
static Tree splayCentralNode(Tree root);
static int unbalanced(Tree node);



// ############### Public Definitions ###############

Tree tree_balance(Tree tree)
{
	if (!tree) { return NULL; }
	
	if (unbalanced(tree))
	{
		tree = splayCentralNode(tree);
		tree_splice(tree, tree_balance(tree->leftTree), LEFT);
		tree_splice(tree, tree_balance(tree->rightTree), RIGHT);
	}
	
	return tree;
}



// ############### Private Definitions ###############

static Tree getCentralNode(Tree root)
{
	if (!root)
	{
		return NULL;
	}
	
	int targetIndex = root->size / 2;
	
	return tree_getByIndex(root, targetIndex);
}



static Tree splayCentralNode(Tree root)
{
	Tree node = getCentralNode(root);
	if (!node) { return NULL; }
	 
	if (tree_splay(node) ) { return NULL; }
	else { return node; }
}



static int unbalanced(Tree node)
{
	if ( node->size < (0x01 << (node->depth - 1)) )
	{
		return 1;
	}
	
	return 0;
}
