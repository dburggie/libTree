#include <Tree.h>
#include <test.h>

int testBuild(int n, int size)
{
	int errors = 0;
	
	int i, depth = 1, MDS = 1;
	
	int sr = (size - 1) / 2;
	int sl = (size - 1) - sr;
	int dl = 1, dr = 1;
	
	for (MDS = 1; MDS < size; MDS = 1 + (MDS << 1) )
	{
		depth++;
		if (MDS < sr) dr++;
		if (MDS < sl) dl++;
	}
	
	Tree tree;
	for (i = 0; i < n; i++)
	{
		tree = tree_build(size);
		
		if (!tree)
		{
			errors++;
			printf("tree_build() returned NULL pointer!\n");
		}
		
		else
		{
			TESTEQ( tree->size, size )
			TESTEQ( tree->depth, depth )
			
			TESTEQ( tree->sizeLeft, sl )
			TESTEQ( tree->depthLeft, dl )
			TEST( sl && !tree->leftTree )
			
			TESTEQ( tree->sizeRight, sr )
			TESTEQ( tree->depthRight, dr )
			TEST( dl && !tree->rightTree )
		}
	}
	
	if (errors)
	{
		printf("ERRORS: was expecting size %i and depth %i.\n", size, depth);
	}
	
	return errors;
}
