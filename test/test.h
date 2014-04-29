#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define FATAL(x,y) printf("%s failed critical test of %s.\n", x, y ); return 1
int testCount = 0;

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

void report(const char * module, int errors, int tests)
{
	if (errors)
	{
		printf("%s: FAILED %i OF %i TESTS\n", module, errors, tests);
	}
	
	else
	{
		printf("%s: passed all of %i tests\n", module, tests);
	}
}

#endif
