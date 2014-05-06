#include <TreePrivate.h>

// ############### Private Declarations ###############

static Tree getCentralNode(Tree root);
static Tree splayCentralNode(Tree root);
static void rotateRight(Tree node);
static void rotateLeft(Tree node);
static int unbalanced(Tree node);

/*
static const int depths[32] = { 
	0x00, 0x01, 0x02, 0x04,
	0x08, 0x10, 0x20, 0x40,
	0x0080, 0x0100,0x0200,0x0400,
	0x0800, 0x1000, 0x2000, 0x4000,
	0x008000, 0x010000, 0x020000, 0x040000,
	0x080000, 0x100000, 0x200000, 0x400000,
	0x00800000, 0x01000000, 0x02000000, 0x01000000,
	0x08000000, 0x10000000, 0x20000000, 0x40000000
}
*/


// ############### Public Definitions ###############

Tree tree_balance(Tree tree)
{
	if (!tree) { return NULL; }
	
	if (unbalanced(tree))
	{
		//printf("tree unbalanced: ");
		//printf("size %i depth %i\n", tree->size, tree->depth);
		
		Tree node = splayCentralNode(tree);
		tree_splice(node, tree_balance(node->leftTree), LEFT);
		tree_splice(node, tree_balance(node->rightTree), RIGHT);
		
		return node;
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
	if (node == root) { return node; }
	
	while (root->parent != node)
	{
		switch (node->gender)
		{
			case LEFT:
				rotateLeft(node);
				break;
			case RIGHT:
				rotateRight(node);
				break;
			default:
				return NULL;
		}
	}
	
	
}

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



static int unbalanced(Tree node)
{
	if ( node->size < (0x01 << (node->depth - 1)) )
	{
		return 1;
	}
	
	return 0;
}
