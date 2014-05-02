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
	
	Tree treeRoot, uleaf, leaf, errleaf;
	
	int i, UNDEX, undex, index, ondex, ONDEX;
	
	int badNodes[size];
	for (i = 0; i < size; i++) badNodes[i] = 0;
	
	for (i = 0; i < n; i++)
	{
		treeRoot = tree_build(size);
		
		if (treeRoot)
		{
			//perform tests
			for (index = 0; index < size; index++)
			{
				UNDEX = index - 2 * size;
				undex = index - size;
				ondex = index + size;
				ONDEX = index + 2 * size;
				
				errleaf = tree_getByIndex(treeRoot, UNDEX);
				if (errleaf) { negoverflowErrors++; }
				
				errleaf = tree_getByIndex(treeRoot, ondex);
				if (errleaf) { overflowErrors++; }
				
				errleaf = tree_getByIndex(treeRoot, ONDEX);
				if (errleaf) { overflowErrors++; }
				
				uleaf = tree_getByIndex(treeRoot, undex);
				leaf = tree_getByIndex(treeRoot, index);
				
				if (!uleaf) { underflowErrors++; }
				if (!leaf) {
					lookupErrors++;
					badNodes[index]++;
				}
				
				if (uleaf && leaf)
				{
					if (uleaf != leaf) { matchErrors++; }
				}
				
			}
			
			tree_destroy(treeRoot);
			
		}
		
		else
		{
			buildErrors++;
		}
	}
	
	int errors = 0;
	int nodes = n * size;
	
	if (buildErrors)
	{
		errors += buildErrors;
		printf("tree_getByIndex(): %i tree build errors ", buildErrors);
		printf("in %i builds.\n", n);
	}
	
	if (negoverflowErrors)
	{
		errors += negoverflowErrors;
		printf("tree_getByIndex(): ");
		printf("%i negative overflow errors ", negoverflowErrors);
		printf("in %i lookups\n", nodes);
	}
	
	if (overflowErrors)
	{
		errors += overflowErrors;
		printf("tree_getByIndex(): ");
		printf("%i overflow errors ", overflowErrors);
		printf("in %i lookups\n", 2 * nodes);
	}
	
	if (underflowErrors)
	{
		errors += underflowErrors;
		printf("tree_getByIndex(): ");
		printf("%i negative index lookup errors ", underflowErrors);
		printf("in %i lookups.\n", nodes);
	}
	
	if (lookupErrors)
	{
		errors += lookupErrors;
		printf("tree_getByIndex(): ");
		printf("%i lookup errors ", lookupErrors);
		printf("in %i lookups.\n", nodes);
		printf("bad nodes (index:count):");
		for (i = 0; i < size; i++)
		{
			if (badNodes[i])
			{
				printf(" (%i:%i)", i, badNodes[i]);
			}
		}
		printf("\n");
	}
	
	if (matchErrors)
	{
		errors += matchErrors;
		printf("tree_getByIndex(): ");
		printf("%i positive/negative index mismatch errors ", matchErrors);
		printf("in %i lookups.\n", nodes);
	}
	
	
	return errors;
}
