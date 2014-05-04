#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdlib.h>



// ############### Type Definitions ###############

typedef struct Node Node;
typedef Node * Tree;

typedef enum SubTreeType SubTreeType;

enum SubTreeType { ROOT, LEFT, RIGHT };



// ############### Method Prototypes ###############

Tree tree_init();
int tree_destroy(Tree tree); //frees this node and both subtrees
int tree_splay(Tree node); //if success, node will be the tree root
int tree_splice(Tree trunk, Tree branch, SubTreeType side);

Tree tree_getByIndex(Tree root, int index);
Tree tree_splayIndex(Tree root, int index); //splays and returns node at index
int tree_insertByIndex(Tree root, Tree node, int index);
Tree tree_insertByKey(Tree root, Tree node);
Tree tree_balance(Tree tree); //returns new subtree root, null on fail

Tree tree_build(int nodes);


// ############### Structure Definitions ###############

struct Node
{
	
	Tree leftTree;
	int sizeLeft; //number of nodes in left subtree
	int depthLeft; //maximum depth of left subtree
	
	Tree rightTree;
	int sizeRight; //number of nodes in right subtree
	int depthRight; //maximum depth of right subtree
	
	int size; //number of nodes in this tree
	int depth; //maximum depth of this tree
	
	Tree parent; //points to parent node, if any
	SubTreeType gender; //flags node as a root or a left or right subtree
	
	int key; //if nodes are sorted by key, this is such a key
	
};

#endif
