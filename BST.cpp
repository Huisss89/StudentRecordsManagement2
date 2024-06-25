#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


//(b) Find the Deepest Nodes or Leaves in the Tree
bool BST::deepestNodes() {
	int height = treeHeight(root, 0, 0);

	if (height==-1) { 
		cout << "\n\t\t\tThe tree is EMPTY!!!" << endl;
		return false;
	}

	else {
		cout << "\n\t\tThe Student ID(s) of the Deepest Node: ";
		printDeepestID(root, height,0); 
		cout << endl;
		return true;
	}
}

//Calculate the Height of the Tree
int BST::treeHeight(BTNode* cur, int height, int currentHeight) {
	if (cur == NULL)
		return -1; 

	if (currentHeight > height) 
		height = currentHeight;

	//Calculate height of left and right subtrees
	if (cur->left != NULL) 
		height = treeHeight(cur->left, height, currentHeight + 1);

	if (cur->right != NULL) 
		height = treeHeight(cur->right, height, currentHeight + 1);

	return height;
}

//Print Student ID of the Deepest Nodes of the Tree
void BST::printDeepestID(BTNode* cur, int deepest, int currentHeight) {
	if (currentHeight == deepest) 
		cout << cur->item.id << " ";

	//Traverse left and right subtrees
	if (cur->left != NULL) 
		printDeepestID(cur->left, deepest, currentHeight + 1);
	
	if (cur->right != NULL)
		printDeepestID(cur->right, deepest, currentHeight + 1);
}


//(c) Display Students' Information
bool BST::display(int order, int source) {
	if (root == NULL) {
		cout << "\nThe tree is EMPTY!!!" << endl;
		return false;
}

	if (source == 1) {
		if (order == 1) 
			ascendingOrder(root, cout);
		else if(order ==2)
			descendingOrder(root, cout);
		else {
			cout << "\nPlease try again!!!" << endl;
		}
	}

	else if (source == 2) {
		ofstream outfile("student-info.txt");
		if (!outfile) {
			cout << "\nUnable to write in text file!" << endl;
			return false;
		}
		if (order == 1)
			ascendingOrder(root, outfile);
		else if (order == 2)
			descendingOrder(root, outfile);
		else {
			cout << "\nPlease try again!!!" << endl;
		}
		outfile.close();
	}

	else {
		cout << "\nPlease try again!" << endl;
	}

	return true;
}

//Traverse Tree in Ascending Order
void BST::ascendingOrder(BTNode* cur, ostream& out) {
	if (cur == NULL)
		return;

	ascendingOrder(cur->left, out);
	cur->item.print(out); //Call print function of Student
	ascendingOrder(cur->right, out);
}

//Traverse Tree in Descending Order
void BST::descendingOrder(BTNode* cur, ostream& out) {
	if (cur == NULL)
		return;

	descendingOrder(cur->right, out);
	cur->item.print(out); //Call print function of Student
	descendingOrder(cur->left, out);
}


//(d) Clone Tree and Print
bool BST::CloneSubtree(BST t1, type item) {
	if (t1.root == NULL) {
		cout << "\nThe tree is EMPTY!!!" << endl;
		return false;
	}
	BTNode* cur;
	cur = t1.root;
	cur = t1.BSTposition(cur, item);
	if (cur == NULL) {
		cout << "\nStudent ID entered does not exist in the record!" << endl;
		return false;
	}
	else {

		CloneSubtree2(cur, item);
	}
	//cout << "\n" << string(58, char(45)) << endl;
	cout << "Print t1 after clone subtree with preOrder: \n";
	cout << string(63, char(45)) << endl;
	t1.preOrderPrint();
	cout << "\n" << string(63, char(45)) << endl;
	cout << "Print t2 after clone subtree with preOrder: \n";
	cout << string(63, char(45)) << endl;
	preOrderPrint();
	cout << string(63, char(45)) << endl;
	return true;
}

//Use to search specific item
void BST::CloneSubtree2(BTNode* cur, type item) {
	if (cur == NULL)
		return;
	insert(cur->item);
	CloneSubtree2(cur->left, item);
	CloneSubtree2(cur->right, item);
}

//Return the address of subtree root
BTNode* BST::BSTposition(BTNode* cur, type item) { 
	if (cur != NULL) {
		//item of studentId is found
		if (cur->item.id == item.id) {
			return cur;
		}
		if (cur->item.id > item.id)
			return BSTposition(cur->left, item);
		else
			return BSTposition(cur->right, item);
	}
	return NULL;
}


//(e)  Level of Nodes
bool BST::printLevelNodes()
{
	BTNode* cur = root;
	if (cur == NULL)
		return false;

	int h = treeHeight(root, 0, 0); //get deepest level of BST
	int i;

	bool order = false; // order = traverse given level from Left to Right 

	for (i = 1; i <= h + 1; i++)
	{
		if (i == 1)
		{
			cout << "\t\t\tLevel 1 nodes: ";
			printGivenLevel(root, i, order);
		}
		else if (i == 2)
		{
			cout << "\t\t\tLevel 2 nodes: ";
			printGivenLevel(root, i, order);
		}
		else if (i == 3)
		{
			cout << "\t\t\tLevel 3 nodes: ";
			printGivenLevel(root, i, order);
		}
		else if (i == 4)
		{
			cout << "\t\t\tLevel 4 nodes: ";
			printGivenLevel(root, i, order);
		}
		cout << "\n";
		order = !order; // reverse order to traverse next level in opposite order
	}
	return true;
}

void BST::printGivenLevel(BTNode* root, int level, int order)
{
	if (root == NULL)
		return;

	if (level == 1)
	{
		cout << root->item.id << " "; //base case, if reach level 1 then print student id
	}
	//will not traverse down further in BST

	else if (level > 1) //recursive case, continue traverse down until level 1 
	{
		if (order)
		{
			printGivenLevel(root->left, level - 1, order);
			printGivenLevel(root->right, level - 1, order);
		}
		else
		{
			printGivenLevel(root->left, level - 1, order);
			printGivenLevel(root->right, level - 1, order);
		}
	}
}


//(f)Print Path
bool BST::printPath()
{
	BTNode* cur = root;
	if (cur == NULL)
		return false;

	int path[1000];
	cout << "\t\tBelow are all the external paths for the tree: " << endl;
	
	printPathsRecur(cur, path, 0);
}

bool BST::printPathsRecur(BTNode* node, int path[], int pathLen)
{
	if (node == NULL)
		return false;

	path[pathLen] = node->item.id;  //append id to path array
	pathLen++;

	if (node->left == NULL && node->right == NULL)  //if no son then print path array
	{
		cout << "\t\t\t\t";
		printArray(path, pathLen);
	}
	else
	{
		printPathsRecur(node->left, path, pathLen);  //if have sons then store inside path array
		printPathsRecur(node->right, path, pathLen);
	}
	return true;
}

void BST::printArray(int number[], int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		cout << number[i] << " ";
	}
	cout << endl;
}

