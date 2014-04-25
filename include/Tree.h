#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdlib.h>



// ############### Type Definitions ###############

typedef struct SplayTree SplayTree;

enum TreeGender { root, left, right };



// ############### Method Prototypes ###############

SplayTree * splaytree_init();
int splaytree_destroy(SplayTree * tree);
int splaytree_splay(SplayTree * node);
int splice(SplayTree * trunk, SplayTree * branch, enum TreeGender side);



// ############### Structure Definitions ###############

struct SplayTree
{
	
	SplayTree * leftTree;
	int sizeLeft;
	
	SplayTree * rightTree;
	int sizeRight;
	
	int size;
	
	SplayTree * parent;
	enum TreeGender gender;
	
	int key;
	
};

#endif
