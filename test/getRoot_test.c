#include <Tree.h>
#include <test.h>


int testGetRoot(int n, int size)
{
	int i, j, errors = 0;
	
	int build = 0;
	int buildSize = 0;
	int nullErr = 0;
	int rootErr = 0;
	int lookup = 0;
	int match = 0;
	
	Tree treeRoot = NULL;
	Tree leaf = NULL;
	
	for (i = 0; i < n; i++)
	{
		treeRoot = tree_build(size);
		
		CASE(!treeRoot, build)
		if (treeRoot->size != size)
		{
			buildSize++;
			treeRoot = NULL;
		}
		
		if (treeRoot)
		{
			leaf = tree_getRoot(NULL);
			CASE(leaf, nullErr);
			for (j = 0; j < size; j++)
			{
				leaf = tree_getByIndex(treeRoot, j);
				CASE(!leaf, lookup)
				
				leaf = tree_getRoot(leaf);
				CASE(!leaf, rootErr)
				if (leaf)
				{
					CASE(leaf != treeRoot, match)
				}
			}
			
			tree_destroy(treeRoot);
		}
	}
	
	errors += genReport(build,n, "tree_getRoot(): bad tree build");
	errors += genReport(buildSize,n, "tree_getRoot(): bad build size");
	errors += genReport(nullErr,n, "tree_getRoot(): bad null arg handling");
	errors += genReport(lookup,n*size, "tree_getRoot(): bad index lookup");
	errors += genReport(rootErr,n*size, "tree_getRoot(): bad root lookup");
	errors += genReport(match,n*size, "tree_getRoot(): node not tree root");
	
	return errors;
}
