#include <Tree.h>
#include <test.h>

int testGetIndex(int n, int size)
{
	int buildErrors = 0,
	    lookupErrors = 0,
	    underflowErrors = 0,
	    matchErrors = 0,
	    negoverflowErrors = 0,
	    overflowErrors = 0;
	
	Tree treeRoot, uleaf, leaf;
	
	int i, UNDEX, undex, index, ondex, ONDEX;
	
	int badNodes[size];
	for (i = 0; i < size; i++) badNodes[i] = 0;
	
	for (i = 0; i < n; i++)
	{
		treeRoot = tree_build(size);
		
		CASE( !treeRoot, buildErrors )
		
		if (treeRoot)
		{
			//perform tests
			for (index = 0; index < size; index++)
			{
				UNDEX = index - 2 * size;
				undex = index - size;
				ondex = index + size;
				ONDEX = index + 2 * size;
				
				CASE( tree_getByIndex(treeRoot, UNDEX), negoverflowErrors )
				CASE( tree_getByIndex(treeRoot, ondex), overflowErrors )
				CASE( tree_getByIndex(treeRoot, ONDEX), overflowErrors )
				
				uleaf = tree_getByIndex(treeRoot, undex);
				leaf = tree_getByIndex(treeRoot, index);
				
				CASE( !uleaf, underflowErrors )
				CASE( !leaf, lookupErrors )
				CASE( !leaf, badNodes[index] )
				
				if (uleaf && leaf)
				{
					CASE( uleaf != leaf, matchErrors )
				}
				
			}
			
			tree_destroy(treeRoot);
			
		}
	}
	
	int errors = 0;
	
	errors += genReport(buildErrors,n, "tree_getByIndex(): tree build errors");
	errors += genReport(negoverflowErrors,n, "tree_getByIndex(): negative overflow errors");
	errors += genReport(overflowErrors,2*n, "tree_getByIndex(): overflow errors");
	errors += genReport(underflowErrors,n, "tree_getByIndex(): underflow errors");
	
	errors += genReport(lookupErrors,n, "tree_getByIndex(): lookup errors");
	if (lookupErrors)
	{
		printf("    bad nodes (index:count):");
		for (i = 0; i < size; i++)
		{
			if (badNodes[i]) { printf(" (%i:%i)", i, badNodes[i]); }
		}
		printf("\n");
	}
	
	errors += genReport(matchErrors,n, "tree_getByIndex(): +/- lookup mismatch");
	
	
	
	return errors;
}
