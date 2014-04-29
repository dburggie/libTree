#include <Tree.h>
#include "test.h"

const char * module = "Tree.c";

int testInit(int n);
int testDestroy(int n);
int testSplice(int n);

int main(void)
{
	int testCount = 0, error = 0;
	
    error += doTest(testInit(100), "tree_init()");
	error += doTest(testDestroy(100), "tree_destroy()");
    error += doTest(testSplice(100), "tree_splice()");

	report(module, error, testCount);
	
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
	
	int errors = 0, i, j;
	
	Tree t, u;
	
	for (i = 0; i < n; i++)
	{
		t = tree_init();
		u = tree_init();
		
		if (tree_splice(t,u, LEFT))
		{
			errors++;
		}
		
		if (t->leftTree != u)
		{
			errors++;
		}
		
		tree_destroy(t);
	}
	
	
	return errors;
	
}






