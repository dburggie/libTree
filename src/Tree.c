#include <TreePrivate.h>




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




int prune(Tree tree, SubTreeType branch)
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


int updateStats(Tree tree)
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



Tree verify(Tree tree)
{
	if (!tree) { return NULL; }
	
	//check match with parent
	switch (tree->gender)
	{
		case LEFT:
			if (!tree->parent) { return tree; }
			if (tree->size != tree->parent->sizeLeft) { return tree; }
			if (tree->depth != tree->parent->depthLeft) { return tree; }
			break;
		case RIGHT:
			if (!tree->parent) { return tree; }
			if (tree->size != tree->parent->sizeRight) { return tree; }
			if (tree->depth != tree->parent->depthRight) { return tree; }
			break;
		case ROOT:
			if (tree->parent) {return tree; }
			break;
		default:
			return tree;	
	}
	
	//check size and depth match
	if (tree->size != 1 + tree->sizeLeft + tree->sizeRight)
	{
		return tree;
	}
	
	if (tree->depth != 1 + MAX(tree->depthLeft, tree->depthRight) )
	{
		return tree;
	}
	
	// verify sub trees
	Tree badChild = NULL;
	badChild = verify(tree->leftTree);
	if (badChild) { return badChild; }
	badChild = verify(tree->rightTree);
	
	// all done
	return badChild;
}







