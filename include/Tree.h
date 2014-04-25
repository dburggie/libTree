#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdlib.h>



// ############### Type Definitions ###############

typedef struct Tree Tree;

enum TreeGender { root, left, right };



// ############### Method Prototypes ###############

Tree * tree_init();
int tree_destroy(Tree * tree);
int tree_splay(Tree * node);
int tree_splice(Tree * trunk, Tree * branch, enum TreeGender side);



// ############### Structure Definitions ###############

struct Tree
{
	
	Tree * leftTree;
	int sizeLeft;
	int depthLeft;
	
	Tree * rightTree;
	int sizeRight;
	int depthRight;
	
	int size;
	int depth;
	
	Tree * parent;
	enum TreeGender gender;
	
	int key;
	
};

#endif
