#include <TreePrivate.h>

// ############### Private Declarations ###############

static void rotateRight(Tree node);
static void rotateLeft(Tree node);



// ############### Public Definitions ###############

int tree_rotate(Tree node)
{
	if (!node)
	{
		return 1;
	}
	
	switch (node->gender)
	{
		case LEFT:
			rotateLeft(node);
			return 0;
		case RIGHT:
			rotateRight(node);
			return 0;
		case ROOT:
			return 0;
		default:
			return 1;
	}
}



// ############### Private Definitions ###############

static void rotateRight(Tree node)
{
	Tree branch = node->leftTree;
	Tree parent = node->parent;
	Tree grandparent = parent->parent;
	SubTreeType parentgender = parent->gender;
	
	tree_splice(parent, branch, RIGHT);
	tree_splice(node, parent, LEFT);
	tree_splice(grandparent, node, parentgender);
}



static void rotateLeft(Tree node)
{
	
	Tree branch = node->rightTree;
	Tree parent = node->parent;
	Tree grandparent = parent->parent;
	SubTreeType parentgender = parent->gender;
	
	tree_splice(parent, branch, LEFT);
	tree_splice(node, parent, RIGHT);
	tree_splice(grandparent, node, parentgender);
	
}



