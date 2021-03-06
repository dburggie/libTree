#include <test.h>

static const char * module = "Tree.c";

static int methodCount = 0;

static void testSuiteInit();
static int doTest(int test, const char * methodName);
static void report(const char * module, int errors);


int main(void)
{
	testSuiteInit();
	
	int errors = 0;
	
	errors += doTest(testInit(100), "tree_init()");
	errors += doTest(testDestroy(100, 100), "tree_destroy()");
	errors += doTest(testSplice(100, 100), "tree_splice()");
	errors += doTest(testBuild(100,100), "tree_build()");
	errors += doTest(testGetIndex(100,100), "tree_getByIndex()");
	errors += doTest(testGetRoot(100,100), "tree_getRoot()");
	errors += doTest(testRotate(100,100), "tree_rotate()");
	errors += doTest(testSplay(100,100), "tree_splay()");
	errors += doTest(testSplayIndex(100,100), "tree_splayIndex()");
	errors += doTest(testBalance(1,100), "tree_balance()");
	
	report(module, errors);
	
	return 0;
}



static void testSuiteInit()
{
	srand(time(NULL));
}



static int doTest(int test, const char * methodName)
{
	methodCount++;
	if (test)
	{
		printf("failure during test of %s\n", methodName);
	}
	
	else
	{
		printf("%s passed tests\n", methodName);
	}
	
	return test;
}


int genReport(int errors, int tests, const char * message)
{
	if (errors)
	{
		printf("%s", message);
		printf(" in %i of %i cases\n", errors, tests);
	}
	
	return errors;
}



static void report(const char * module, int errors)
{
	if (errors)
	{
		printf("%s: FAILED %i TESTS IN %i METHODS\n", module, errors, methodCount);
	}
	
	else
	{
		printf("%s: passed all tests of %i methods\n", module, methodCount);
	}
}
