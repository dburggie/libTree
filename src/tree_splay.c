#include <TreePrivate.h>

// ############### Private Declarations ###############

static void rotateLeft(Tree node);
static void rotateRight(Tree node);



// ############### Public Definitions ###############

int tree_splay(Tree node)
{
	if (!node) { return 1; }
	
	//is our node already the root node?
	if (node->gender == ROOT) { return 0; }
	
	 //this shouldn't ever be null, but safety first
	if (!node->parent) { return 1; }
	
	//swap with parent, taking handedness into account
	switch (node->gender) {
		
		case LEFT:
			rotateLeft(node);
			return tree_splay(node);
		
		case RIGHT:
			rotateRight(node);
			return tree_splay(node);
		
		default:
			return 1;
	}
}



// ############### Private Definitions ###############

static void rotateLeft(Tree node)
{
	Tree branch = node->leftTree;
	Tree parent = node->parent;
	Tree grandparent = parent->parent;
	SubTreeType parentgender = parent->gender;
	
	tree_splice(parent, branch, RIGHT);
	tree_splice(node, parent, LEFT);
	tree_splice(grandparent, node, parentgender);
}



static void rotateRight(Tree node)
{
	
	Tree branch = node->rightTree;
	Tree parent = node->parent;
	Tree grandparent = parent->parent;
	SubTreeType parentgender = parent->gender;
	
	tree_splice(parent, branch, LEFT);
	tree_splice(node, parent, RIGHT);
	tree_splice(grandparent, node, parentgender);
	
}



