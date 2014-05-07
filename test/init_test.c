#include <Tree.h>
#include <test.h>

static int isNull(Tree t);
static int parent(Tree t);
static int leftTree(Tree t);
static int rightTree(Tree t);
static int treeSize(Tree t);
static int treeDepth(Tree t);



int testInit(int n)
{
    int i, errors = 0;
    
    int nullErrors = 0;
    int parentErrors = 0;
    int leftErrors = 0;
    int rightErrors = 0;
    int sizeErrors = 0;
    int depthErrors = 0;
    
    Tree t;

    for (i = 0; i < n; i++)
    {
        t = tree_init();
        if (t)
        {
        	CASE(isNull(t), nullErrors)
        	CASE(parent(t), parentErrors)
        	CASE(leftTree(t), leftErrors)
        	CASE(rightTree(t), rightErrors)
        	CASE(treeSize(t), sizeErrors)
        	CASE(treeDepth(t), depthErrors)
        	
        	free(t);
        }
    }
    
    errors += genReport(nullErrors, n, "tree_init(): returned null pointers");
    errors += genReport(parentErrors, n, "tree_init(): non-null parent");
    errors += genReport(leftErrors,n,"tree_init(): non-null left sub-tree");
    errors += genReport(rightErrors,n,"tree_init(): non-null right sub-tree");
    errors += genReport(sizeErrors,n,"tree_init(): uninitialized tree sizes");
    errors += genReport(depthErrors,n,"tree_init(): uninitialized tree depths");

    return errors;
}



static int isNull(Tree t)
{
	return (t) ? 0 : 1;
}

static int parent(Tree t)
{
	return (t->parent) ? 1 : 0;
}

static int leftTree(Tree t)
{
	return (t->leftTree) ? 1 : 0;
}

static int rightTree(Tree t)
{
	return (t->rightTree) ? 1 : 0;
}

static int treeSize(Tree t)
{
	return (t->sizeLeft || t->sizeRight || t->size != 1) ? 1 : 0;
}

static int treeDepth(Tree t)
{
	return (t->depthLeft || t->depthRight || t->depth != 1) ? 1 : 0;
}

