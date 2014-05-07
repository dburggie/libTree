#include <TreePrivate.h>

// ############### Private Declarations ###############

static int buildSubTree(Tree trunk, int size);



// ############### Public Definitions ###############

Tree tree_build(int nodes)
{
	if (nodes < 1)
	{
		return NULL;
	}
	
	Tree tree = tree_init();
	if (!tree) return NULL;
	
	if (buildSubTree(tree, nodes))
	{
		tree_destroy(tree);
		return NULL;
	}
	
	return tree;
	
	
}



// ############### Private Definitions ###############

static int buildSubTree(Tree trunk, int size)
{
	
	if (size < 1) return 0;
	size--;
	int rightSize = size / 2;
	int leftSize = size - rightSize;
	
	if (leftSize > 0)
	{
		Tree left = tree_init();
		if (!left) return 1;
		if (buildSubTree(left, leftSize)) return 1;
		if (tree_splice(trunk, left, LEFT)) return 1;
	}
	
	if (rightSize > 0)
	{
		Tree right = tree_init();
		if ( !right ) return 1;
		if ( buildSubTree(right, rightSize) ) return 1;
		if ( tree_splice(trunk, right, RIGHT) ) return 1;
	}
	
	return 0;
	
}
