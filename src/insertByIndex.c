#include <TreePrivate.h>

// ############### Private Declarations ###############

static Tree getLargestChild(Tree node);
static int trackChanges(Tree node, int depth, SubTreeType gender);


// ############### Public Definitions ###############

int tree_insertByIndex(Tree root, Tree node, int index)
{
	
	if (!root || !node)
	{
		return 1;
	}
	
	//handle underflow
	if (index < 0)
	{
		index += root->size;
		if (index < 0)
		{
			return 1;
		}
		
		else
		{
			return tree_insertByIndex(root,node,index);
		}
	}
	
	//overflow
	if (index > root->size)
	{
		return 1;
	}
	
	Tree leaf = tree_getByIndex(root, index);
	SubTreeType gender;

	if (!leaf) //handle append case
	{
		leaf = getLargestChild(root);
		gender = RIGHT;
	}
	
	else if (leaf->leftTree)
	{
		leaf = getLargestChild(leaf->leftTree);
		gender = LEFT;
	}
	
	tree_splice(leaf, node, gender);
	trackChanges(leaf, 1, gender);

	return 0;

	
}



// ############### Private Definitions ###############

static Tree getLargestChild(Tree node)
{
	
	if (!node)
	{
		return NULL;
	}

	if (node->rightTree)
	{
		return node->rightTree;
	}

	else
	{
		return node;
	}
	
}



static int trackChanges(Tree node, int depth, SubTreeType gender)
{
	
	if (!node)
	{
		return 1;
	}

	switch (gender)
	{
		case LEFT:
			node->sizeLeft = node->leftTree->size;
			node->size = 1 + node->sizeLeft + node->sizeRight;

			if (depth)
			{
				node->depthLeft = node->leftTree->depth;
				depth = node->depthLeft > node->depthRight;
			}

			break;
		
		case RIGHT:
			node->sizeRight = node->rightTree->size;
			node->size = 1 + node->sizeLeft + node->sizeRight;

			if (depth)
			{
				node->depthRight = node->rightTree->depth;
				depth = node->depthLeft < node->depthRight;
			}

			break;
		
		case ROOT:
			return 0;
		
	}
	
	if (depth)
	{
		node->depth = 1 + MAX(node->depthLeft, node->depthRight);
	}
	
	return trackChanges(node->parent, depth, node->gender);
	
}
