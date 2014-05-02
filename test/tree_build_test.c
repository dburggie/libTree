#include <Tree.h>
#include <test.h>

int testBuild(int n, int size)
{
	int i, errors = 0;
	
	int null = 0;
	int badArg = 0;
	
	int books_S = 0;
	int books_D = 0;
	int books_SL = 0;
	int books_DL = 0;
	int books_SR = 0;
	int books_DR = 0;
	
	int left_null = 0;
	int left_depth = 0;
	int left_size = 0;
	int right_null = 0;
	int right_depth = 0;
	int right_size = 0;
	
	int maxDepthSize = 1, depth = 1;
	int depthLeft = 1, depthRight = 1;
	int sizeRight = (size - 1) / 2;
	int sizeLeft = size - 1 - sizeRight;
	
	while (maxDepthSize < size)
	{
		//if size overflows the max size at this depth we increment our depth
		depth++;
		
		if (maxDepthSize < sizeLeft)
		{
			depthLeft++;
		}
		
		if (maxDepthSize < sizeRight)
		{
			depthRight++;
		}
		
		maxDepthSize = 1 + 2 * maxDepthSize; // get next 2^n - 1
	}
	
	
	Tree tree;
	for (i = 0; i < n; i++)
	{
		
		CASE(tree_build(-1), badArg)
		CASE(tree_build(0), badArg)
		
		tree = tree_build(size);
		
		CASE( !tree, null )
		
		if (tree)
		{
			CASE( tree->size != size, books_S )
			CASE( tree->depth != depth, books_D )
			CASE( tree->sizeLeft != sizeLeft, books_SL )
			CASE( tree->depthLeft != depthLeft, books_DL )
			CASE( tree->sizeRight != sizeRight, books_SR )
			CASE( tree->depthRight != depthRight, books_DR )
			
			CASE( depthLeft && !tree->leftTree, left_null )
			CASE( !depthLeft && tree->leftTree, left_null )
			if (tree->leftTree)
			{
				CASE( tree->leftTree->depth != depthLeft, left_depth )
				CASE( tree->leftTree->size != sizeLeft, left_size )
			}
			
			CASE( depthRight && !tree->rightTree, right_null )
			CASE( !depth && tree->leftTree, right_null )
			if (tree->rightTree)
			{
				CASE( tree->rightTree->depth != depthRight, right_depth )
				CASE( tree->rightTree->size != sizeRight, right_size )
			}
			
			tree_destroy(tree);
		}
		
		
		
	}
	
	errors += genReport(books_S,n, "tree_build(): bad root node size");
	errors += genReport(books_D,n, "tree_build(): bad root node depth");
	errors += genReport(books_SL,n,"tree_build(): bad root node left size");
	errors += genReport(books_DL,n,"tree_build(): bad root node left depth");
	errors += genReport(books_SR,n,"tree_build(): bad root node right size");
	errors += genReport(books_DR,n,"tree_build(): bad root node right depth");
	
	errors += genReport(left_null,n, "tree_build(): bad left tree existence");
	errors += genReport(left_depth,n,"tree_build(): bad left tree depth");
	errors += genReport(left_size,n, "tree_build(): bad left tree size");
	errors += genReport(right_null,n, "tree_build(): bad right tree existence");
	errors += genReport(right_depth,n,"tree_build(): bad right tree depth");
	errors += genReport(right_size,n, "tree_build(): bad right tree size");
	
	return errors;
}
