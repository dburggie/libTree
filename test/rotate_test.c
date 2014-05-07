#include <Tree.h>
#include <test.h>



int testRotate(int n, int size)
{
	
	int i, errors;
	
	int build = 0;
	int lookup = 0;
	int leftRotate = 0;
	int leftUp = 0;
	int leftDown = 0;
	int rightRotate = 0;
	int rightUp = 0;
	int rightDown = 0;
	int root = 0;
	int nullErr = 0;
	int destroy = 0;
	
	Tree tree;
	Tree leaf;
	Tree parent;
	
	
	for (i = 0; i < n; i++)
	{
		tree = tree_build(size);
		
		CASE(!tree, build)
		
		if (tree)
		{
			CASE(tree_rotate(tree) || tree->gender != ROOT, root)
			
			parent = tree_getByIndex(tree, rand() % size);
			CASE(!parent, lookup);
			
			leaf = parent->leftTree;
			if (!leaf) { CASE(!tree_rotate(leaf), nullErr) }
			else
			{
				CASE( tree_rotate(leaf), leftRotate )
				CASE( leaf->rightTree != parent, leftUp )
				CASE( parent->parent != leaf, leftDown )
			}
			
			leaf = parent->rightTree;
			if (!leaf) { CASE(!tree_rotate(leaf), nullErr) }
			else
			{
				CASE( tree_rotate(leaf), rightRotate )
				CASE( leaf->leftTree != parent, rightUp )
				CASE( parent->parent != leaf, rightDown )
			}
			
			
			CASE( tree_destroy(tree_getRoot(tree)) != size, destroy )
		}
	}
	
	errors += genReport(build,n,"testRotate(): bad tree_build() call");
	errors += genReport(root,n,"tree_rotate(): bad root node case");
	errors += genReport(lookup,n,"testRotate(): bad tree_getByIndex() call");
	errors += genReport(nullErr,2*n,"tree_rotate(): bad null case");
	errors += genReport(leftRotate,n,"tree_rotate(): bad rotate left");
	errors += genReport(leftUp,n,"tree_rotate(): bad child splice left");
	errors += genReport(leftDown,n,"tree_rotate(): bad parent splice left");
	errors += genReport(rightRotate,n,"tree_rotate(): bad rotate right");
	errors += genReport(rightUp,n,"tree_rotate(): bad child splice right");
	errors += genReport(rightDown,n,"tree_rotate(): bad parent splice right");
	errors += genReport(destroy,n,"testRotate(): bad tree_destroy() call");
	
	return errors;
}
