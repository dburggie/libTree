#include <Tree.h>
#include <test.h>

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
