#include <Tree.h>

#define MAX(x,y) (x > y) ? x : y
#define MIN(x,y) (x < y) ? x : y


// ############### Private Method Prototypes ################

static int recursiveDestroy(Tree self);
static void rotateLeft(Tree node);
static void rotateRight(Tree node);
static int prune(Tree tree, TreeGender branch);
static int updateStats(Tree tree);



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
	tree->depth = 0;
	
	tree->parent = NULL;
	tree->gender = root;
	
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
	if (node->gender == root) { return 0; }
	
	 //this shouldn't ever be null, but safety first
	if (!node->parent) { return 1; }
	
	//swap with parent, taking handedness into account
	switch (node->gender) {
		
		case left:
			rotateLeft(node);
			return tree_splay(node);
		
		case right:
			rotateRight(node);
			return tree_splay(node);
		
		default:
			return 1;
	}
}



int tree_splice(Tree trunk, Tree branch, TreeGender side)
{
	
	//handle a null trunk
	if (!trunk )
	{
		if (!branch || side != root) { return 1; }
		
		return prune(branch->parent, branch->gender);
	}
	
	//handle last true error case
	if (side == root) { return 1; }
	
	//exit on prune if no branch
	if (!branch) { return prune(trunk, side); }
	
	//prune off old branch
	prune(trunk, side);
	prune(branch->parent, branch->gender);
	
	//splice branch onto trunk
	switch (side)
	{
		case left:
			trunk->leftTree = branch;
			trunk->sizeLeft = branch->size;
			break;
		case right:
			trunk->rightTree = branch;
			trunk->sizeRight = branch->size;
			break;
		default:
			return 1;
	}
	
	//splice trunk onto branch and clean up tree sizes
	updateStats(trunk);
	branch->parent = trunk;
	branch->gender = side;
	
	return 0;
	
}



// ############### Private Method Definitions ###############

static int recursiveDestroy(Tree self)
{
	
	int errors = 0;
	
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
	TreeGender parentgender = parent->gender;
	
	tree_splice(parent, branch, right);
	tree_splice(node, parent, left);
	tree_splice(grandparent, node, parentgender);
	
}



static void rotateRight(Tree node)
{
	
	Tree branch = node->leftTree;
	Tree parent = node->parent;
	Tree grandparent = parent->parent;
	TreeGender parentgender = parent->gender;
	
	tree_splice(parent, branch, left);
	tree_splice(node, parent, right);
	tree_splice(grandparent, node, parentgender);
	
}




static int prune(Tree tree, TreeGender branch)
{
	
	if (!tree)
	{
		return (branch == root);
	}
	
	switch (branch)
	{
		case root:
			return 1;
		
		case left:
			tree->leftTree = NULL;
			tree->sizeLeft = 0;
			tree->size = 1 + tree->sizeRight;
			
			if (tree->depthLeft > tree->depthRight)
			{
				tree->depth = 1 + tree->depthRight;
			}
			
			tree->depthLeft = 0;
			return 0;
		
		case right:
			tree->rightTree = NULL;
			tree->sizeRight = 0;
			tree->size = 1 + tree->sizeLeft;
			
			if (tree->depthRight > tree->depthLeft)
			{
				tree->depth = 1 + tree->depthLeft;	
			}
			
			tree->depthRight = 0;
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



