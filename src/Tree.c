#include <SplayTree.h>




// ############### Private Method Prototypes ################

static int recursiveDestroy(SplayTree * self);
static void splayLeft(SplayTree * node);
static void splayRight(SplayTree * node);
static int prune(SplayTree * tree, enum TreeGender branch);



// ############### Public Method Definitions ###############

SplayTree * splaytree_init()
{
	SplayTree * tree = (SplayTree *) malloc(sizeof(SplayTree));
	
	if (!tree) return NULL;
	
	//initialize left sub-tree
	tree->leftTree = NULL;
	tree->sizeLeft = 0;
	
	//initialize right sub-tree
	tree->rightTree = NULL;
	tree->sizeRight = 0;
	
	tree->size = 1;
	
	tree->parent = NULL;
	tree->gender = root;
	
	return tree;
}

int splaytree_destroy(SplayTree * tree)
{
	if (!tree) return 1;
	
	prune(tree->parent, tree->gender);
	
	return recursiveDestroy(tree);
	
}


int splaytree_splay(SplayTree * node)
{
	if (!node) { return 1; }
	
	//is our node already the root node?
	if (node->gender == root) { return 0; }
	
	 //this shouldn't ever be null, but safety first
	if (!node->parent) { return 1; }
	
	//swap with parent, taking handedness into account
	switch (node->gender) {
		
		case left:
			splayLeft(node);
			return splaytree_splay(node);
		
		case right:
			splayRight(node);
			return splaytree_splay(node);
		
		default:
			return 1;
	}
}



int splice(SplayTree * trunk, SplayTree * branch, enum TreeGender side)
{
	
	//handle a null trunk
	if (!trunk )
	{
		if (!branch || side != root) { return 1; }
		
		branch->parent = NULL;
		branch->gender = root;
		return 0;
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
	trunk->size = 1 + trunk->sizeLeft + trunk->sizeRight;
	branch->parent = trunk;
	branch->gender = side;
	
	return 0;
	
}



// ############### Private Method Definitions ###############

static int recursiveDestroy(SplayTree * self)
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



static void splayLeft(SplayTree * node)
{
	
	SplayTree * branch = node->leftTree;
	SplayTree * parent = node->parent;
	SplayTree * grandparent = parent->parent;
	enum TreeGender parentgender = parent->gender;
	
	splice(parent, branch, right);
	splice(node, parent, left);
	splice(grandparent, node, parentgender);
	
}



static void splayRight(SplayTree * node)
{
	
	SplayTree * branch = node->leftTree;
	SplayTree * parent = node->parent;
	SplayTree * grandparent = parent->parent;
	enum TreeGender parentgender = parent->gender;
	
	splice(parent, branch, left);
	splice(node, parent, right);
	splice(grandparent, node, parentgender);
	
}




static int prune(SplayTree * tree, enum TreeGender branch)
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
			return 0;
		
		case right:
			tree->rightTree = NULL;
			tree->sizeRight = 0;
			tree->size = 1 + tree->sizeLeft;
			return 0;
		
		default:
			return 1;
	}
	
}



