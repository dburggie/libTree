#include <Tree.h>
#include <test.h>



int testBalance(int n, int size)
{
	
	int errors = 0, i, left, right;
	
	int init = 0;
	int build = 0;
	int splice = 0;
	int nullErr = 0;
	int trivial = 0;
	int exec = 0;
	int rootErr = 0;
	int oldroot = 0;
	int balance = 0;
	
	Tree root, leaf;
	
	for (i = 0; i < n; i++)
	{
		CASE( tree_balance(NULL), nullErr )
		
printf("handled null case\n");
		
		for (left = 0; left < size - 1; left++)
		{
			right = size - 1 - left;
			
			root = tree_init();
			CASE( !root, init )
			CASE( !tree_balance(root), trivial )
			
			leaf = tree_build(left);
			CASE( left && !leaf, build )
			CASE( tree_splice(root, leaf, LEFT), splice )
			
			leaf = tree_build(right);
			CASE( right && !leaf, build )
			CASE( tree_splice(root, leaf, RIGHT), splice )
			
			leaf = tree_balance(root);
			
			CASE( !leaf, exec )
			
			CASE( leaf->gender != ROOT, rootErr )
			CASE( leaf->parent, rootErr )
			
			if ( leaf != root )
			{
				CASE( root->gender == ROOT, oldroot )
				CASE( !root->parent, oldroot )
			}
			
			CASE( leaf->size < (0x01 << (leaf->depth - 1)), balance )
			tree_destroy(leaf);
		}
	}
	
	errors += genReport(nullErr,n,"tree_balance(): bad handling of null arg");
	errors += genReport(init,n*size,"tree_balance(): bad tree_init() call");
	errors += genReport(trivial,n*size,"tree_balance(): bad trivial case");
	errors += genReport(build,2*n*size,"tree_balance(): bad tree_build() call");
	errors += genReport(splice,2*n*size,"tree_balance(): bad tree_splice() call");
	errors += genReport(exec,n*size,"tree_balance(): bad return of NULL");
	errors += genReport(rootErr,2*n*size,"tree_balance(): new root has parents");
	errors += genReport(oldroot,2*n*(size-1),"tree_balance(): old root is root");
	errors += genReport(balance,n*size,"tree_balance(): tree not balanced");
	
	return errors;
}
