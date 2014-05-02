#include <Tree.h>
#include <test.h>

int testDestroy(int n, int size)
{
	int i, errors = 0;
	Tree t;
	
	int nullErrors = 0;
	int sizeErrors = 0;
	
	for (i = 0; i < n; i++)
	{
		t = tree_build(size);
		
		CASE(!tree_destroy(NULL), nullErrors)
		CASE(tree_destroy(t) != size, sizeErrors)
		
	}
	
	if (nullErrors)
	{
		errors += genReport(nullErrors, n, "tree_destroy(): destroyed a null tree");
	}
	
	if (sizeErrors)
	{
		errors += genReport(sizeErrors, n, "tree_destroy(): reports bad leaf count");
	}
	
	return errors;
}
