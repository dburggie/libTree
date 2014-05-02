#ifndef TREE_PRIVATE_H
#define TREE_PRIVATE_H

#include <Tree.h>


#define MAX(x,y) ( (x > y) ? x : y )
#define MIN(x,y) ( (x < y) ? x : y )

int prune(Tree tree, SubTreeType branch);
int updateStats(Tree tree);
Tree verify(Tree tree);

#endif
