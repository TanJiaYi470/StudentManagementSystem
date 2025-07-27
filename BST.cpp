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


void BST::preOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}

//change function from cout ->ostream 
void BST::inOrderPrint(ostream& out) {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root, out);// do normal process
	out << endl;
}

void BST::inOrderPrint2(BTNode* cur, ostream& out) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left, out);
	cur->item.print(out);
	inOrderPrint2(cur->right, out);
}

//new function for displaying descending code
void BST::descendingPrint(ostream& out) {
	if (root == NULL) return;// handle special case
	else descendingPrint2(root, out);// do normal process
	out << endl;
}

void BST::descendingPrint2(BTNode* cur, ostream& out) {

	if (cur == NULL) return;

	descendingPrint2(cur->right, out);
	cur->item.print(out);
	descendingPrint2(cur->left, out);
}

void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
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


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
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
	BTNode* cur = new BTNode(newItem);
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


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
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

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
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


void BST::case2(BTNode* pre, BTNode* cur) {

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


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

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

//(b)

int BST::tree_height(BTNode* root) {       //find the height of tree
	if (root == nullptr)
		return 0;

	int left_side = tree_height(root->left);
	int right_side = tree_height(root->right);

	// Return the maximum height between the left and right subtrees
	return 1 + max(left_side, right_side);
}

bool BST::deepestNodes(BTNode* root, int level, int height) {     //find the deepest node

	if (root == NULL) {
		return false; // Empty tree
	}

	// Recur for left and right subtrees
	deepestNodes(root->left, level + 1, height);
	deepestNodes(root->right, level + 1, height);

	// If current node is at the deepest level, print it
	if (level == height - 1)
		cout << root->item.id << "  ";
	return true;
}




//(c)
bool BST::isEmpty() {
	return root == nullptr;
}

bool BST::display(int order, int source)
{
	type student;
	//check whether the tree got value or not
	if (isEmpty()) {
		cout << "This tree is empty." << endl;
		return false;
	}

	//ascending
	if (order == 1)
	{
		if (source == 1)
		{
			inOrderPrint(cout);
			return true;
		}
		else if (source == 2)
		{
			ofstream myFile("student-info.txt");
			if (!myFile) {
				cout << "Error opening the file! " << endl;
				return false;
			}
			inOrderPrint(myFile);
			myFile.close();
			cout << "Student info being written successfully" << endl;
			return true;
		}
		else
		{
			cout << "Your selection for source is not correct. Please try to select (1 for screen, 2 for in file): ";
			return false;
		}
	}
	//descending
	else if (order == 2)
	{
		if (source == 1)
		{
			descendingPrint(cout);
			return true;
		}
		else if (source == 2)
		{
			ofstream myFile("student-info.txt");
			if (!myFile) {
				cout << "Error opening the file! " << endl;
				return false;
			}
			descendingPrint(myFile);
			myFile.close();
			cout << "Student info being written successfully" << endl;
			return true;
		}
		else
		{
			cout << "Your selection for source is not correct. Please try to select (1 for screen, 2 for in file): ";
			return false;
		}
	}
	else {
		cout << "Your order is not correct, please try to select (1 for ascending, 2 for descending): ";
		return false;
	}
}

//(d)	
bool BST::CloneSubtree2(BST t1, type item) {
	if (t1.root == nullptr) {
		return false;  // If the subtree is empty, return false
	}

	BTNode* cur = t1.root;
	bool found = false;

	// Check if the current node matches the target item
	if (cur->item.id == item.id) {
		preOrderInsert(cur);  // Insert the current node into the clone
		found = true;  // Mark as found
	}

	// Recursively process the left subtree
	BST leftSubtree;
	leftSubtree.root = cur->left;  // Create a BST object for the left subtree
	found = CloneSubtree2(leftSubtree, item) || found;  // Continue processing

	// Recursively process the right subtree
	BST rightSubtree;
	rightSubtree.root = cur->right;  // Create a BST object for the right subtree
	found = CloneSubtree2(rightSubtree, item) || found;  // Continue processing

	return found;  // Return whether we found and cloned the node
}

bool BST::CloneSubtree(BST t1, type item) {
	if (t1.root == nullptr) {
		cout << "Tree is empty." << endl;
		return false;
	}
	return CloneSubtree2(t1, item);  // Return the result of CloneSubtree2
}

void BST::preOrderInsert(BTNode* cur) {
	if (cur == NULL) return;
	insert(cur->item);
	preOrderInsert(cur->left);
	preOrderInsert(cur->right);
}


//e
bool BST::printLevelNodes(int height) {
	if (root == NULL)
		return false;
	else {
		for (int level = 1; level <= height; level++) {
			cout << "Level " << level << " nodes: ";
			printLevelNodes2(root, level);
			cout << endl;
		}
		return true;
	}
}

void BST::printLevelNodes2(BTNode* cur, int numlevel) { //level = numlevel, print nodes at the level 1, 2, 3 and so on...
	if (cur == NULL) return;
	if (numlevel == 1) { //numlevel 1 = level 1, correct, print
		cout << cur->item.id << " ";
	}
	else {
		printLevelNodes2(cur->left, numlevel - 1); //recursive
		printLevelNodes2(cur->right, numlevel - 1);
	}
}

//f
bool BST::printpath() {
	if (root == NULL)
		return false;

	else {
		cout << "Below are all the external paths for the tree : " << endl;
		cout << endl;
		int RTLpath = 0;//number of id node in a path
		int path[1000];//to store ID along the path from root to leaf
		printpath2(root, path, RTLpath);
		return true;
	}
}

void BST::printpath2(BTNode* cur, int path[], int RTLpath) {
	if (cur == NULL) return;

	path[RTLpath] = cur->item.id;//store stu id in path array at RTLpath
	RTLpath++; //increment 1 to move to the next

	if (cur->left == NULL && cur->right == NULL) {
		pathArray(path, RTLpath);//when until leaf node, print out the path
	}
	else {
		printpath2(cur->left, path, RTLpath);//recursive
		printpath2(cur->right, path, RTLpath);
	}
}

void BST::pathArray(int path[], int RTLpath) {
	for (int k = 0; k < RTLpath; k++) { //start at path[0] = root, so <
		cout << path[k] << " "; // print the id that store at the position
	}
	cout << endl;
}
