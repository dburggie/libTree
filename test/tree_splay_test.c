#include <Tree.h>
#include <test.h>

int testSplay(int n, int size)
{
	int errors = 0;
	int buildErrors = 0;
	int splayErrors = 0;
	int matchErrors = 0;
	int rootErrors = 0;
	int leftSubTreeErrors = 0;
	int rightSubTreeErrors = 0;
	
	int i, index;
	
	Tree root, leaf;
	
	int badNodes[size];
	int splayedNodes[size];
	for (i = 0; i < size; i++)
	{
		badNodes[i] = 0;
		splayedNodes[i] = 0;
	}
	
	for (i = 0; i < n; i++)
	{
		root = tree_build(size);
		if (root)
		{
			
			for (index = 0; index < size; index++)
			{
				leaf = tree_getByIndex(root,index);
				if (leaf) leaf->key = index;
			}
			
			index = rand() % size;
			leaf = tree_getByIndex(root, index);
			
			if ( tree_splay(leaf) )
			{
				splayErrors++;
				tree_destroy(root);
			}
			
			
			else
			{
				
				splayedNodes[index]++;
				
				root = leaf;
				
				if (root->key != index)
				{
					matchErrors++;
					badNodes[index]++;
				}
				
				if (root->gender != ROOT || root->parent)
				{
					rootErrors++;
				}
				
				if (root->sizeLeft != index)
				{
					leftSubTreeErrors++;
				}
				
				if (root->sizeRight != size - 1 - index)
				{
					rightSubTreeErrors++;
				}
				
				tree_destroy(root);
			}
		}
		
		else
		{
			buildErrors++;
		}
	}
	
	if (buildErrors)
	{
		errors += buildErrors;
		printf("tree_splay(): failed building tree ");
		printf("%i of %i times\n", buildErrors, n);
	}
	
	if (splayErrors)
	{
		errors += splayErrors;
		printf("tree_splay(): returned null ");
		printf("%i of %i times\n", splayErrors, n);
	}
	
	if (matchErrors)
	{
		errors += matchErrors;
		printf("tree_splay(): splayed node not at correct index ");
		printf("%i of %i times\n", matchErrors, n);
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
	
	if (rootErrors)
	{
		errors += rootErrors++;
		printf("tree_splay(): splayed node not properly set as root ");
		printf("%i of %i times\n", rootErrors, n);
	}
	
	if (leftSubTreeErrors)
	{
		errors += leftSubTreeErrors;
		printf("tree_splay(): bad left sub-tree size after splay ");
		printf("%i of %i times\n", leftSubTreeErrors, n);
	}
	
	if (rightSubTreeErrors)
	{
		errors += rightSubTreeErrors;
		printf("tree_splay(): bad right sub-tree size after splay ");
		printf("%i of %i times\n", rightSubTreeErrors, n);
	}
	
	if (errors)
	{
		printf("nodes splayed (index:count):");
		for (i = 0; i < size; i++)
		{
			if (splayedNodes[i])
			{
				printf(" (%i:%i)", i, splayedNodes[i]);
			}
		}
		printf("\n");
	}
	
	return errors;
}
