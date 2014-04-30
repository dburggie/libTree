#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define FATAL(x,y) printf("%s failed critical test of %s.\n", x, y ); return 1
int testCount = 0;

void testSuiteInit()
{
	srand(time(NULL));
}

int doTest(int test, const char * methodName)
{
	testCount++;
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

void report(const char * module, int errors)
{
	if (errors)
	{
		printf("%s: FAILED %i TESTS IN %i METHODS\n", module, errors, testCount);
	}
	
	else
	{
		printf("%s: passed all tests of %i methods\n", module, testCount);
	}
}

#endif
