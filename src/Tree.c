#include <Tree.h>

#define MAX(x,y) ( (x > y) ? x : y )
#define MIN(x,y) ( (x < y) ? x : y )


// ############### Private Method Prototypes ################

static int recursiveDestroy(Tree self);
static void rotateLeft(Tree node);
static void rotateRight(Tree node);
static int prune(Tree tree, SubTreeType branch);
static int updateStats(Tree tree);
static int buildSubTree(Tree trunk, int size);
static Tree getNodeAtIndex(Tree tree, int index);



// ############### Public Method Definitions ###############

Tree tree_init()
{
	Tree tree = (Tree) malloc(sizeof(Node));
	
	if (!tree) return NULL;
	
	//initialize left sub-tree
	tree->leftTree = NULL;
	tree->sizeLeft = 0;
	tree->depthLeft = 0;
	
	//initialize right sub-tree
	tree->rightTree = NULL;
	tree->sizeRight = 0;
	tree->depthRight = 0;
	
	tree->size = 1;
	tree->depth = 1;
	
	tree->parent = NULL;
	tree->gender = ROOT;
	
	return tree;
}

int tree_destroy(Tree tree)
{
	if (!tree) return 1;
	
	prune(tree->parent, tree->gender);
	
	return recursiveDestroy(tree);
	
}


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



int tree_splice(Tree trunk, Tree branch, SubTreeType side)
{
	
	//handle a null trunk
	if (!trunk )
	{
		if (!branch || side != ROOT) { return 1; }
		
		return prune(branch->parent, branch->gender);
	}
	
	//handle last true error case
	if (side == ROOT) { return 1; }
	
	//exit on prune if no branch
	if (!branch) { return prune(trunk, side); }
	
	//prune off old branch
	prune(trunk, side);
	prune(branch->parent, branch->gender);
	
	//splice branch onto trunk
	switch (side)
	{
		case LEFT:
			trunk->leftTree = branch;
			trunk->sizeLeft = branch->size;
			trunk->depthLeft = branch->depth;
			break;
		case RIGHT:
			trunk->rightTree = branch;
			trunk->sizeRight = branch->size;
			trunk->depthRight = branch->depth;
			break;
		default:
			return 1;
	}
	
	//splice trunk onto branch and clean up tree sizes
	trunk->size = 1 + trunk->sizeLeft + trunk->sizeRight;
	trunk->depth = 1 + MAX(trunk->depthLeft, trunk->depthRight);
	branch->parent = trunk;
	branch->gender = side;
	
	return 0;
	
}




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



// ############### Private Method Definitions ###############

static int recursiveDestroy(Tree self)
{
	
	int errors = 0;

    if (!self)
    {
        return 1;
    }
	
	if (self->leftTree)
	{
		errors += recursiveDestroy(self->leftTree);
	}
	
	if (self->rightTree)
	{
		errors += recursiveDestroy(self->rightTree);
	}
	
	free(self);
	
	return errors;
	
}



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




static int prune(Tree tree, SubTreeType branch)
{
	
	if (!tree)
	{
		return (branch != ROOT);
	}
	
	switch (branch)
	{
		case ROOT:
			
			if (tree->gender == ROOT) { return 0; }
			else { return prune(tree->parent, tree->gender); }
			
		case LEFT:
			
			if (tree->leftTree)
			{
				tree->leftTree->gender = ROOT;
				tree->leftTree->parent = NULL;
				
				tree->leftTree = NULL;
				tree->sizeLeft = 0;
				tree->size = 1 + tree->sizeRight;
				
				if (tree->depthLeft > tree->depthRight)
				{
					tree->depth = 1 + tree->depthRight;
				}
				
				tree->depthLeft = 0;
			}
			
			return 0;
		
		case RIGHT:
			
			if (tree->rightTree)
			{
				tree->rightTree->gender = ROOT;
				tree->rightTree->parent = NULL;
				
				tree->rightTree = NULL;
				tree->sizeRight = 0;
				tree->size = 1 + tree->sizeLeft;
				
				if (tree->depthRight > tree->depthLeft)
				{
					tree->depth = 1 + tree->depthLeft;	
				}
				
				tree->depthRight = 0;
			}
			
			return 0;
		
		default:
			return 1;
	}
	
}


static int updateStats(Tree tree)
{
	if (!tree) { return 1; }
	
	
	
	if (tree->leftTree)
	{
		tree->sizeLeft = tree->leftTree->size;
		tree->depthLeft = tree->leftTree->depth;
	}
	
	else
	{
		tree->sizeLeft = 0;
		tree->depthLeft = 0;
	}
	
	
	
	if (tree->rightTree)
	{
		tree->sizeRight = tree->rightTree->size;
		tree->depthRight = tree->rightTree->depth;
	}
	
	else
	{
		tree->sizeRight = 0;
		tree->depthRight = 0;
	}
	
	
	
	tree->depth = 1 + MAX(tree->depthLeft, tree->depthRight);
	tree->size = 1 + tree->sizeLeft + tree->sizeRight;
	
	return 0;
}




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

