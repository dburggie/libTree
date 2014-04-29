#include <Tree.h>
#include "test.h"

#define TEST(exp) if (exp) { errors++; printf("Failed: " #exp "\n"); }

const char * module = "Tree.c";

int testInit(int n);
int testDestroy(int n);
int testSplice(int n);

int main(void)
{
	int errors = 0;
	
    errors += doTest(testInit(100), "tree_init()");
	errors += doTest(testDestroy(100), "tree_destroy()");
    errors += doTest(testSplice(100), "tree_splice()");

	report(module, errors, testCount);
	
	return 0;
}



int testInit(int n)
{
    int i, errors = 0;
    Tree t;

    for (i = 0; i < n; i++)
    {
        t = tree_init();
        if (!t)
        {
            errors++;
        }
        tree_destroy(t);
    }

    return errors;
}



int testDestroy(int n)
{
    int i,j, errors = 0;
    Tree t;

    for (i = 0; i < n; i++)
    {
        t = tree_init();
        for  (j = 0; j < i; j++)
        {
            t->parent = tree_init();
            t->gender = LEFT;
            t = t->parent;
        }

        errors += tree_destroy(t);
        
    }
    
    if (!tree_destroy(NULL))
    {
        errors += 1;
    }

    return errors;
}

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






