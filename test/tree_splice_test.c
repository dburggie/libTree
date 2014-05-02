#include <Tree.h>
#include <test.h>

int testSplice(int n)
{
	
	int errors = 0, i;
	
	Tree t, u;
	
	for (i = 0; i < n; i++)
	{
		t = tree_init();
		
		//handle error cases
		
		//both null is bad
		TEST( !tree_splice(NULL, NULL, ROOT) )
		
		//cant put a branch on nothing
		TEST( !tree_splice(NULL, t, LEFT) )
		TEST( !tree_splice(NULL, t, RIGHT) )
		
		//this makes t a root tree and should be fine
		TEST( tree_splice(NULL, t, ROOT) )
		
		u = tree_init();
		//can't root onto a branch
		TEST( !tree_splice(t,u,ROOT) )
		
		TEST( tree_splice(t,u,LEFT) )
		TEST( t->leftTree != u )
		
		u = tree_init();
		TEST( tree_splice(t,u,RIGHT) )
		TEST( t->rightTree != u )
		
		
		tree_destroy(t);
		
	}
	
	
	return errors;
	
}
