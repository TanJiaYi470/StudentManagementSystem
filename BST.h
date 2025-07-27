#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

	int		count;
	BTNode* root;

	// print operation for BST (same as BT)					
	void preOrderPrint2(BTNode*);	// recursive function for preOrderPrint()
	void inOrderPrint2(BTNode*, ostream&);	// recursive function for inOrderPrint()
	void postOrderPrint2(BTNode*);	// recursive function for postOrderPrint()

	// sample operation (extra functions) - same as BT
	void countNode2(BTNode*, int&);		// recursive function for countNode()
	bool fGS2(type, BTNode*);					// recursive function for findGrandsons(): to find the grandfather
	void fGS3(BTNode*, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found

	// basic functions for BST
	void insert2(BTNode*, BTNode*);		// recursive function for insert() of BST
	void case3(BTNode*);					// recursive function for remove()
	void case2(BTNode*, BTNode*);		// recursive function for remove()
	bool remove2(BTNode*, BTNode*, type);	// recursive function for remove()



	// basic functions for BST
	BST();
	bool empty();
	int size();
	bool insert(type);		// insert an item into a BST
	bool remove(type);			// remove an item from a BST

	// print operation for BST (same as BT)
	void preOrderPrint();			// print BST node in pre-order manner
	void inOrderPrint(ostream&);			// print BST node in in-order manner
	void postOrderPrint();			// print BST node in post-order manner
	void topDownLevelTraversal();	// print BST level-by-level

	//c
	//additional operation to print out order in descending
	void descendingPrint(ostream&);
	void descendingPrint2(BTNode*, ostream&);


	// sample operation (extra functions) - same as BT
	int countNode();		// count number of tree nodes
	bool findGrandsons(type);	// find the grandsons of an input father item

	//(b)
	int tree_height(BTNode* root);
	bool deepestNodes(BTNode*, int, int);


	//question c
	bool isEmpty();
	bool display(int, int);

	//(D)
	bool CloneSubtree(BST t1, type item);
	bool CloneSubtree2(BST t1, type item);
	void preOrderInsert(BTNode* cur);

	//question e
	bool printLevelNodes(int);
	void printLevelNodes2(BTNode*, int);

	//question f
	bool printpath();
	void printpath2(BTNode*, int[], int);
	void pathArray(int[], int);
};




#endif