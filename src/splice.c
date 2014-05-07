#include <TreePrivate.h>

// ############### Private Declarations ###############

// first declaration



// ############### Public Definitions ###############

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



// ############### Private Definitions ###############

// first definition



