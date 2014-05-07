#include <Tree.h>
#include <test.h>

int testSplice(int n, int size)
{
	
	int errors = 0, i;
	
	int nullSplice = 0;
	int noTrunk = 0;
	int rootSplice = 0;
	int badBranch = 0;
	
	int leftSplice = 0;
	int leftMatch = 0;
	int leftSize = 0;
	int leftDepth = 0;
	
	int rightSplice = 0;
	int rightMatch = 0;
	int rightSize = 0;
	int rightDepth = 0;
	
	int sizeErr = 0;
	int depthErr = 0;
	
	int targetSize;
	int targetDepth;
	
	Tree t, u;
	
	if (size < 1) { size = 1; }
	
	for (i = 0; i < n; i++)
	{
		t = tree_init();
		
		//both null is bad
		CASE( !tree_splice(NULL, NULL, ROOT), nullSplice )
		
		//cant put a branch on nothing
		CASE( !tree_splice(NULL, t, LEFT), noTrunk )
		CASE( !tree_splice(NULL, t, RIGHT), noTrunk )
		
		//this makes t a root tree and should be fine
		CASE( tree_splice(NULL, t, ROOT), rootSplice )
		
		u = tree_build(size);
		//can't root onto a branch
		CASE( !tree_splice(t,u,ROOT), badBranch )
		
		CASE( tree_splice(t,u,LEFT), leftSplice )
		CASE( t->leftTree != u , leftMatch )
		CASE( t->leftTree->size != t->sizeLeft, leftSize )
		CASE( t->leftTree->depth != t->depthLeft, leftDepth )
		
		u = tree_build(size);
		CASE( tree_splice(t,u,RIGHT), rightSplice )
		CASE( t->rightTree != u , rightMatch )
		CASE( t->rightTree->size != t->sizeLeft, rightSize )
		CASE( t->rightTree->depth != t->depthLeft, rightDepth )
		
		
		targetSize = 1 + t->sizeLeft + t->sizeRight;
		if (t->depthLeft > t->depthRight) { targetDepth = 1 + t->depthLeft; }
		else { targetDepth = 1 + t->depthRight; }
		
		CASE( t->size != targetSize, sizeErr )
		CASE( t->depth != targetDepth, depthErr )
		
		tree_destroy(t);
		
	}
	
	errors += genReport(nullSplice,n, "tree_splice(): no fail on null args");
	errors += genReport(noTrunk,2*n, "tree_splice(): no fail on null trunk");
	errors += genReport(rootSplice,n, "tree_splice(): fails making node root");
	errors += genReport(badBranch,n, "tree_splice(): no fail with bad branch arg");
	errors += genReport(leftSplice,n, "tree_splice(): failed splice to left");
	errors += genReport(leftMatch,n, "tree_splice(): left splice node mismatch");
	errors += genReport(leftSize,n, "tree_splice(): bad left sub-tree size");
	errors += genReport(leftDepth,n, "tree_splice(): bad left sub-tree depth");
	errors += genReport(rightSplice,n, "tree_splice(): failed splice to right");
	errors += genReport(rightMatch,n, "tree_splice(): right splice node mismatch");
	errors += genReport(rightSize,n, "tree_splice(): bad right sub-tree size");
	errors += genReport(rightDepth,n, "tree_splice(): bad right sub-tree depth");
	errors += genReport(sizeErr,n, "tree_splice(): bad tree size");
	errors += genReport(depthErr,n, "tree_splice(): bad tree depth");
	
	return errors;
	
}
