#include <Tree.h>
#include "test.h"

#define TEST(exp) if (exp) { errors++; printf("Failed: " #exp "\n"); }

#define TESTEQ( X, Y ) if (X != Y) { \
	errors++; printf("Failied: " #X " != " #Y " :: %i != %i\n", X, Y); }

const char * module = "Tree.c";

int testInit(int n);
int testDestroy(int n);
int testSplice(int n);
int testBuild(int n, int size);

int testGetIndex(int n, int size);

int testSplay(int n, int size);


int main(void)
{
	testSuiteInit();
	
	int errors = 0;
	
    errors += doTest(testInit(100), "tree_init()");
	errors += doTest(testDestroy(100), "tree_destroy()");
	
    errors += doTest(testSplice(100), "tree_splice()");
	errors += doTest(testBuild(100,100), "tree_build()");
	errors += doTest(testGetIndex(100,100), "tree_getByIndex()");
	errors += doTest(testSplay(10,10), "tree_splay()");
	
	report(module, errors);
	
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



int testBuild(int n, int size)
{
	int errors = 0;
	
	int i, depth = 1, MDS = 1;
	
	int sr = (size - 1) / 2;
	int sl = (size - 1) - sr;
	int dl = 1, dr = 1;
	
	for (MDS = 1; MDS < size; MDS = 1 + (MDS << 1) )
	{
		depth++;
		if (MDS < sr) dr++;
		if (MDS < sl) dl++;
	}
	
	Tree tree;
	for (i = 0; i < n; i++)
	{
		tree = tree_build(size);
		
		if (!tree)
		{
			errors++;
			printf("tree_build() returned NULL pointer!\n");
		}
		
		else
		{
			TESTEQ( tree->size, size )
			TESTEQ( tree->depth, depth )
			
			TESTEQ( tree->sizeLeft, sl )
			TESTEQ( tree->depthLeft, dl )
			TEST( sl && !tree->leftTree )
			
			TESTEQ( tree->sizeRight, sr )
			TESTEQ( tree->depthRight, dr )
			TEST( dl && !tree->rightTree )
		}
	}
	
	if (errors)
	{
		printf("ERRORS: was expecting size %i and depth %i.\n", size, depth);
	}
	
	return errors;
}




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






