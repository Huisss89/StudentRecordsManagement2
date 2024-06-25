#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

		int		count;
		BTNode	*root;

		// print operation for BST (same as BT)					
		void preOrderPrint2(BTNode *);	// recursive function for preOrderPrint()
		void inOrderPrint2(BTNode *);	// recursive function for inOrderPrint()
		void postOrderPrint2(BTNode *);	// recursive function for postOrderPrint()

		// sample operation (extra functions) - same as BT
		void countNode2(BTNode *, int &);		// recursive function for countNode()
		bool fGS2(type, BTNode *);					// recursive function for findGrandsons(): to find the grandfather
		void fGS3(BTNode *, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found
		
		// basic functions for BST
		void insert2(BTNode *, BTNode *);		// recursive function for insert() of BST
		void case3(BTNode *);					// recursive function for remove()
		void case2(BTNode *, BTNode *);		// recursive function for remove()
		bool remove2(BTNode *, BTNode *, type);	// recursive function for remove()



		// basic functions for BST
		BST();
		bool empty();
		int size();
		bool insert (type);		// insert an item into a BST
		bool remove(type);			// remove an item from a BST
		
		// print operation for BST (same as BT)
		void preOrderPrint();			// print BST node in pre-order manner
		void inOrderPrint();			// print BST node in in-order manner
		void postOrderPrint();			// print BST node in post-order manner
		void topDownLevelTraversal();	// print BST level-by-level

		// sample operation (extra functions) - same as BT
		int countNode();		// count number of tree nodes
		bool findGrandsons(type);	// find the grandsons of an input father item


		bool deepestNodes(); //Find the deepest nodes in the tree
		int treeHeight(BTNode*, int, int); //Find the height of a tree
		void printDeepestID(BTNode *, int, int); //Print Student ID of the deepest nodes
		
		bool display(int, int); //Display student's info
		void ascendingOrder(BTNode*, ostream&); //Traverse tree in ascending order
		void descendingOrder(BTNode*, ostream&); //Traverse tree in descending order

		bool CloneSubtree(BST, type); //Clone tree and print
		void CloneSubtree2(BTNode*, type); //Search specific item
		BTNode* BSTposition(BTNode*, type); //Return the address of subtree root

		bool printLevelNodes(); //Level of nodes
		void printGivenLevel(BTNode* root, int level, int ltr);

		bool printPath(); //Print path
		bool printPathsRecur(BTNode* node, int path[], int pathLen);
		void printArray(int number[], int len);
};




#endif