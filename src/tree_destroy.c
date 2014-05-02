#include <TreePrivate.h>

// ############### Private Declarations ###############

static int recursiveDestroy(Tree self);



// ############### Public Definitions ###############

int tree_destroy(Tree tree)
{
	if (!tree) return 0;
	
	prune(tree->parent, tree->gender);
	
	return recursiveDestroy(tree);
	
}



// ############### Private Definitions ###############

static int recursiveDestroy(Tree self)
{
	
	int killCount = 0;

    if (!self)
    {
        return 0;
    }
	
	if (self->leftTree)
	{
		killCount += recursiveDestroy(self->leftTree);
	}
	
	if (self->rightTree)
	{
		killCount += recursiveDestroy(self->rightTree);
	}
	
	free(self);
	
	return 1 + killCount;
	
}



