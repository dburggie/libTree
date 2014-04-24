#include <SplayTree.h>




// ############### Private Method Prototypes ################

static int recursiveDestroy(SplayTree * self);
static void splayLeft(SplayTree * node);
static void splayRight(SplayTree * node);



// ############### Public Method Definitions ###############

SplayTree * splaytree_init()
{
	SplayTree * self = (SplayTree *) malloc(sizeof(SplayTree));
	self->leftChild = NULL; self->rightChild = NULL;
	
	self->parent = NULL;
	self->childType = root;
	
	return self;
}

int splaytree_destroy(SplayTree * self)
{
	if (!self) return 1;
	
	//disconnect from parent
	if (self->childType != root)
	{
		if (!self->parent)
		{
			return 1;
		}
		
		if (self->childType == left)
		{
			self->parent->leftChild = NULL;
		}
		
		else
		{
			self->parent->rightChild = NULL;
		}
	}
	
	return recursiveDestroy(self);
	
}


int splaytree_splay(SplayTree * node)
{
	if (!node) { return 1; }
	
	//is our node already the root node?
	if (node->childType == root) { return 0; }
	
	 //this shouldn't ever be null, but safety first
	if (!node->parent) { return 1; }
	
	//swap with parent, taking handedness into account
	switch (node->childType) {
		
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


// ############### Private Method Definitions ###############

static int recursiveDestroy(SplayTree * self)
{
	
	int errors = 0;
	
	if (self->leftChild)
	{
		errors += recursiveDestroy(self->leftChild);
	}
	
	if (self->rightChild)
	{
		errors += recursiveDestroy(self->rightChild);
	}
	
	free(self);
	
	return errors;
	
}



static void splayLeft(SplayTree * node)
{
	SplayTree * parent = node->parent;
	SplayTree * grandparent = parent->parent;
	
	node->childType = parent->childType;
	node->parent = grandparent;
	
	parent->rightChild = node->leftChild;
	node->leftChild = parent;
	
	if (grandparent)
	{
		if (node->childType == left)
		{
			grandparent->leftChild = node;
		}
		
		else
		{
			grandparent->rightChild = node;
		}
	}
}



static void splayRight(SplayTree * node)
{
	SplayTree * parent = node->parent;
	SplayTree * grandparent = parent->parent;
	
	node->childType = parent->childType;
	node->parent = grandparent;
	
	parent->leftChild = node->rightChild;
	node->rightChild = parent;
	
	if (grandparent)
	{
		if (node->childType == left)
		{
			grandparent->leftChild = node;
		}
		
		else
		{
			grandparent->rightChild = node;
		}
	}
}
