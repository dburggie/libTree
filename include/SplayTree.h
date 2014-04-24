#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdlib.h>



// ############### Type Definitions ###############

typedef struct SplayTree SplayTree;

enum ChildType { root, left, right };



// ############### Method Prototypes ###############

SplayTree * splaytree_init();
int splaytree_destroy(SplayTree * tree);
int splaytree_splay(SplayTree * node);



// ############### Structure Definitions ###############

struct SplayTree
{
	
	SplayTree * leftChild;
	SplayTree * rightChild;
	
	SplayTree * parent;
	enum ChildType childType;
	
	int key;
	
};

#endif
