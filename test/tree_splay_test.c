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
		
		CASE( !root, buildErrors )
		
		if (root)
		{
			
			//label each node with it's index
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
				
				CASE( root->key != index, matchErrors )
				CASE( root->key != index, badNodes[index] )
				
				CASE( root->gender != ROOT || root->parent, rootErrors )
				CASE( root->sizeLeft != index, leftSubTreeErrors )
				CASE( root->sizeRight != size - 1 - index, rightSubTreeErrors )
				
				tree_destroy(root);
			}
		}
	}
	
	errors += genReport(buildErrors,n,"tree_splay: build error");
	errors += genReport(splayErrors,n,"tree_splay: splay fail");
	errors += genReport(matchErrors,n,"tree_splay: splayed wrong node");
	if (matchErrors)
	{
		printf("    bad splays (index:count):");
		for (i = 0; i < size; i++)
		{
			if (badNodes[i]) { printf(" (%i:%i)", i, badNodes[i]); }
		}
		printf("\n");
	}
	errors += genReport(rootErrors,n,"tree_splay: root parent not updated");
	errors += genReport(leftSubTreeErrors,n,"tree_splay: bad left tree size");
	errors += genReport(rightSubTreeErrors,n,"tree_splay: bad right tree size");
	
	if (errors)
	{
		printf("    nodes splayed (index:count):");
		for (i = 0; i < size; i++)
		{
			if (splayedNodes[i]) { printf(" (%i:%i)", i, splayedNodes[i]); }
		}
		printf("\n");
	}
	
	return errors;
}
