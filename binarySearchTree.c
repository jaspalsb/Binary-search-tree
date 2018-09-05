/*
*Author: Jaspal Bainiwal
*Date: 05/20/2018
*Description: Implementation of the binary search tree data structure.


*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bst.h"
#include "structs.h"

struct Node {
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree {
	struct Node *root;
	int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
function to initialize the binary search tree.
param tree
pre: tree is not null
post:	tree size is 0
root is null
*/

void initBSTree(struct BSTree *tree)
{
	tree->cnt = 0;
	tree->root = 0;
}

/*
function to create a binary search tree.
param: none
pre: none
post: tree->count = 0
tree->root = 0;
*/

struct BSTree*  newBSTree()
{
	struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
	assert(tree != 0);

	initBSTree(tree);
	return tree;
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
pre: none
post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
	if (node != 0) {
		_freeBST(node->left);
		_freeBST(node->right);
		free(node);
	}
}

/*
function to clear the nodes of a binary search tree
param: tree    a binary search tree
pre: tree ! = null
post: the nodes of the tree are deallocated
tree->root = 0;
tree->cnt = 0
*/
void clearBSTree(struct BSTree *tree)
{
	if (tree->root != 0) {
		_freeBST(tree->root);
		tree->root = 0;
	}
	tree->cnt = 0;
}

/*
function to deallocate a dynamically allocated binary search tree
param: tree   the binary search tree
pre: tree != null;
post: all nodes and the tree structure itself are deallocated.
*/
void deleteBSTree(struct BSTree *tree)
{
	if (tree->root != 0) {
		clearBSTree(tree);
	}
	free(tree);
}

/*----------------------------------------------------------------------------*/
/*
function to determine if  a binary search tree is empty.

param: tree    the binary search tree
pre:  tree is not null
*/
int isEmptyBSTree(struct BSTree *tree) { return (tree->cnt == 0); }

/*
function to determine the size of a binary search tree

param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { return tree->cnt; }

/*----------------------------------------------------------------------------*/
/*
recursive helper function to add a node to the binary search tree.
HINT: You have to use the compare() function to compare values.
param:  cur	the current root node
val	the value to be added to the binary search tree
pre:	val is not null
*/
struct Node *_addNode(struct Node *cur, TYPE val)
{
	/*First create our struct node, then test where current node is equalt to null that means we 
	have reached a leaf so we add the node there. Else if it is not equal to ndoe then we use
	recursion to reach that base case null, then we bottom out and add the nodes back left and right sides.
	I am using the example from the lectures to complete this function*/

	struct Node *newnode;

	if (cur == NULL)
	{
		//Now we have reached the base case which is a leaf that has its left or right as null.
		newnode = malloc(sizeof(struct Node));
		assert(newnode != 0);
		newnode->val = val;
		newnode->left = newnode->right = 0;
		return newnode;
	}
	/*using the compare function that is written by the developer so that type can be any type*/
	if (compare(val, cur->val) == -1)
	{
		cur->left = _addNode(cur->left, val);
	}
	else if (compare(val, cur->val) == 1)
	{
		cur->right = _addNode(cur->right, val);
	}
	return cur;
}

/*
function to add a value to the binary search tree
param: tree   the binary search tree
val		the value to be added to the tree

pre:	tree is not null
val is not null
pose:  tree size increased by 1
tree now contains the value, val
*/
void addBSTree(struct BSTree *tree, TYPE val)
{
	tree->root = _addNode(tree->root, val);
	tree->cnt++;
}


/*
function to determine if the binary search tree contains a particular element
HINT: You have to use the compare() function to compare values.
param:	tree	the binary search tree
val		the value to search for in the tree
pre:	tree is not null
val is not null
post:	none
*/

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{
	/*From our BST 3 lecture it talks about the compare function, if the value is the same
	then compare returns 0. If the value is less than then it returns -1 else if it is greater
	then return 1. So by using this compare function I will setup up the tree to the node. Then call the
	compare function if it returns 0 then this contains function will return 1. else if the it returns -1 
	that means I need to go left on by BST else if it returns 1 that means I need to go right. If after all
	the traversing I reach a leaf and the tree is now at NULL left or right that means the tree does not 
	contain the value so I will return 0*/

	assert(tree != 0);
	struct Node *current = tree->root;

	while (current != NULL)
	{
		if (compare(val, current->val) == -1)
		{
			//compare returns -1 that means the value is less than the current nodes value which means I need
			//to go left so now set the current node to the next left child
			current = current->left;
		}
		else if (compare(val, current->val) == 1)
		{
			//this compare function returns a 1 that means that the val is greater than the current nodes value
			//so I need to go to the right child
			current = current->right;
		}
		else if (compare(val, current->val) == 0)
		{
			//lastly hopefully we have reached a node that matches the value that we are searching for 
			//in this case I will then just return true from the function
			return 1;
		}
	}
	return 0;
}

/*
helper function to find the left most child of a node
return the value of the left most child of cur
param: cur		the current node
pre:	cur is not null
post: none
*/

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{
	/*Left mode is easy I find the left most node by traversing left until I hit left 
	node whose left child is NULL. At that point I will return the value of the left most
	node.*/

	assert(cur != 0);

	while (cur->left != NULL)
	{
		//keep traversing left by making the current node the next left node.
		cur = cur->left;
	}

	return cur->val;
}


/*
recursive helper function to remove the left most child of a node
HINT: this function returns cur if its left child is NOT NULL. Otherwise,
it returns the right child of cur and free cur.

Note:  If you do this iteratively, the above hint does not apply.

param: cur	the current node
pre:	cur is not null
post:	the left most node of cur is not in the tree
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
	/*so for this function I will be using the recursion method.
	The way the recursion works is that I am passsed a current node in this case cur.
	If currents left child is not null that means I am not at the left most node yet, so I 
	make another call to the removeLeftmostn function recursively. Once I reach the base case
	which is when I reach the left node is null that means this is the most left I can go.
	So at this point the node could have a special case where there is a subtree to the right 
	side. So I want to remove this leftmost node then replace it with the right child subtree. 
	Then when the function is returning recursively it will return the current node and be
	set to the previous funtion calls cur->left. */

	//create my right subtree node
	struct Node *rightSubtree;
	//if current node has left child then I need to call function recursively and I set the recursion
	//equal to cur->left because once it returns now this will be the new current nodes left.
	if (cur->left != NULL)
	{
		cur->left = _removeLeftMost(cur->left);
		return cur;
	}
	else if (cur->left == NULL)
	{
		/*now I have reached the left most node I need to replace it with the right child subtree
		then free the current node. So I do this by making the new node that I created equal to the
		left most childs which is cur to be equal to its right child. Once that is done I return this
		new node of the right subtree to the previous recursive call and that will set this right subtree
		equal to the previous nodes->left.*/
		rightSubtree = cur->right;
		free(cur);
		return rightSubtree;
	}
	else
	{
		//added this because of this warning  control reaches end of non-void function [-Wreturn-type]
		return cur;
	}
}
/*
recursive helper function to remove a node from the tree
HINT: You have to use the compare() function to compare values.
param:	cur	the current node
val	the value to be removed from the tree
pre:	val is in the tree
cur is not null
val is not null
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
	/*I am using the psuedocode from the lectures and the worksheet 29 function _nodeRemoveBST to
	help me write this function. So first I am comparing the value to see if this is the one that I 
	do want to remove by calling the compare function written by the developer(me). Now if it is the
	correct node then I want to take care of the special case where the node that is to be removed
	does not have a right child, if it doesn't have a right child then I need to use the left node.
	Else if there is a right node then I do the normal way by making the node to be removed the leftmost
	of the right node. Now if the value is not equal then I use the compare function if it is less than
	then that means I need to search in the left half. Else if the value is greater than the node then 
	I need to search in the right half, these functions are done recursively.*/

	if (compare(val, cur->val) == 0)
	{
		if (cur->right == 0)
		{
			struct Node *temp = cur->left;
			free(cur);
			return temp;
		}
		else
		{
			cur->val = _leftMost(cur->right);
			cur->right = _removeLeftMost(cur->right);
		}
	}
	else if (compare(val, cur->val) == -1)
	{
		cur->left = _removeNode(cur->left, val);
	}
	else
	{
		cur->right = _removeNode(cur->right, val);
	}
	return cur;
}
/*
function to remove a value from the binary search tree
param: tree   the binary search tree
val		the value to be removed from the tree
pre:	tree is not null
val is not null
val is in the tree
pose:	tree size is reduced by 1
*/
void removeBSTree(struct BSTree *tree, TYPE val)
{
	if (containsBSTree(tree, val)) {
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}

/*----------------------------------------------------------------------------*/


#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
	if (cur == 0) return;
	printf("(");
	printNode(cur->left);
	/*Call print_type which prints the value of the TYPE*/
	print_type(cur->val);
	printNode(cur->right);
	printf(")");
}

void printTree(struct BSTree *tree) {
	if (tree == 0) return;
	printNode(tree->root);
}
/*----------------------------------------------------------------------------*/

#endif


#if 1

// Test value stuff -----

struct TestValues
{
	struct data* values;
	int n;
};

void initValue(struct data* value, int number, const char* name)
{
	value->number = number;
	value->name = malloc((strlen(name) + 1) * sizeof(char));
	strcpy(value->name, name);
}

void freeValue(struct data* value)
{
	free(value->name);
}

struct TestValues* createValues()
{
	struct TestValues* values = malloc(sizeof(struct TestValues));
	values->n = 4;
	values->values = malloc(values->n * sizeof(struct data));

	initValue(&(values->values[0]), 50, "rooty");
	initValue(&(values->values[1]), 13, "lefty");
	initValue(&(values->values[2]), 110, "righty");
	initValue(&(values->values[3]), 10, "lefty of lefty");

	return values;
}

void destroyValues(struct TestValues* values)
{
	for (int i = 0; i < values->n; ++i)
	{
		freeValue(&(values->values[i]));
	}
	free(values->values);
	free(values);
}

// -----

void printTestResult(int predicate, char *nameTestFunction, char *message) {
	if (predicate)
		printf("%s(): PASS %s\n", nameTestFunction, message);
	else
		printf("%s(): FAIL %s\n", nameTestFunction, message);
}

/**
* Tests adding 4 nodes to the BST.
*/
void testAddNode()
{
	struct TestValues* tv = createValues();
	struct BSTree *tree = newBSTree();

	// Add all values to the tree
	for (int i = 0; i < tv->n; ++i)
	{
		addBSTree(tree, &(tv->values[i]));
		if (tree->cnt != i + 1)
		{
			printf("addNode() test: FAIL to increase count when inserting\n");
			return;
		}
	}

	// Check that root node is rooty
	if (tree->root->val != &(tv->values[0]))
	{
		printf("addNode() test: FAIL to insert 50 as root\n");
		return;
	}
	else
	{
		printf("addNode() test: PASS when adding 50 as root\n");
	}

	if (tree->root->left->val != &(tv->values[1]))
	{
		printf("addNode() test: FAIL to insert 13 as left child of root\n");
		return;
	}
	else
	{
		printf("addNode() test: PASS when adding 13 as left of root\n");
	}

	if (tree->root->right->val != &(tv->values[2]))
	{
		printf("addNode() test: FAIL to insert 110 as right child of root\n");
		return;
	}
	else
	{
		printf("addNode() test: PASS when adding 110 as right of root\n");
	}

	if (tree->root->left->left->val != &(tv->values[3]))
	{
		printf("addNode() test: FAIL to insert 10 as left child of left of root\n");
		return;
	}
	else
	{
		printf("addNode() test: PASS when adding 10 as left of left of root\n");
	}

	deleteBSTree(tree);
	destroyValues(tv);
}

/**
* Tests that the BST contains the added elements,
* and that it does not contain an element that was not added.
*/
void testContainsBSTree()
{
	struct TestValues* tv = createValues();
	struct BSTree *tree = newBSTree();

	// Create value not added to the tree
	struct data notInTree;
	notInTree.number = 111;
	notInTree.name = "not in tree";

	// Add all other values to the tree
	for (int i = 0; i < tv->n; ++i)
	{
		addBSTree(tree, &(tv->values[i]));
	}

	printTestResult(containsBSTree(tree, &(tv->values[0])), "containsBSTree", "when test containing 50 as root");
	printTestResult(containsBSTree(tree, &(tv->values[1])), "containsBSTree", "when test containing 13 as left of root");
	printTestResult(containsBSTree(tree, &(tv->values[2])), "containsBSTree", "when test containing 110 as right of root");
	printTestResult(containsBSTree(tree, &(tv->values[3])), "containsBSTree", "when test containing 10 as left of left of root");

	printTestResult(!containsBSTree(tree, &notInTree), "containsBSTree", "when test containing 111, which is not in the tree");

	deleteBSTree(tree);
	destroyValues(tv);
}

/**
* Tests leftMost.
*/
void testLeftMost()
{
	struct TestValues* tv = createValues();
	struct BSTree *tree = newBSTree();

	for (int i = 0; i < tv->n; ++i)
	{
		addBSTree(tree, &(tv->values[i]));
	}

	printTestResult(_leftMost(tree->root) == &(tv->values[3]), "_leftMost", "left most of root");
	printTestResult(_leftMost(tree->root->left) == &(tv->values[3]), "_leftMost", "left most of left of root");
	printTestResult(_leftMost(tree->root->left->left) == &(tv->values[3]), "_leftMost", "left most of left of left of root");
	printTestResult(_leftMost(tree->root->right) == &(tv->values[2]), "_leftMost", "left most of right of root");

	deleteBSTree(tree);
	destroyValues(tv);
}

/**
* Tests left-most removal of 3 nodes.
*/
void testRemoveLeftMost()
{
	struct TestValues* tv = createValues();
	struct BSTree *tree = newBSTree();

	for (int i = 0; i < tv->n; ++i)
	{
		addBSTree(tree, &(tv->values[i]));
	}

	struct Node* oldRoot = tree->root;
	tree->root = _removeLeftMost(tree->root);
	--(tree->cnt);
	printTestResult(tree->root == oldRoot, "_removeLeftMost", "removing leftmost of root 1st try");

	tree->root->right = _removeLeftMost(tree->root->right);
	--(tree->cnt);
	printTestResult(tree->root->right == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");

	oldRoot = tree->root;
	tree->root = _removeLeftMost(tree->root);
	--(tree->cnt);
	printTestResult(tree->root == oldRoot, "_removeLeftMost", "removing leftmost of root 2st try");

	deleteBSTree(tree);
	destroyValues(tv);
}

/**
* Tests removal of all nodes.
*/
void testRemoveNode()
{
	struct TestValues* tv = createValues();
	struct BSTree *tree = newBSTree();

	for (int i = 0; i < tv->n; ++i)
	{
		addBSTree(tree, &(tv->values[i]));
	}

	tree->root = _removeNode(tree->root, &(tv->values[3]));
	--(tree->cnt);
	printTestResult(tree->root->val == &(tv->values[0]) && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");

	tree->root = _removeNode(tree->root, &(tv->values[2]));
	--(tree->cnt);
	printTestResult(tree->root->val == &(tv->values[0]) && tree->root->right == NULL, "_removeNode", "remove right of root 2st try");

	tree->root = _removeNode(tree->root, &(tv->values[1]));
	--(tree->cnt);
	printTestResult(tree->root->val == &(tv->values[0]) && tree->root->left == 0, "_removeNode", "remove right of root 3st try");

	tree->root = _removeNode(tree->root, &(tv->values[0]));
	--(tree->cnt);
	printTestResult(tree->root == NULL, "_removeNode", "remove right of root 4st try");

	deleteBSTree(tree);
	destroyValues(tv);
}

/*

Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]) {

	//After implementing your code, please uncommnet the following calls to the test functions and test your code 

	testAddNode();

	printf("\n");
	testContainsBSTree();

	printf("\n");
	testLeftMost();

	printf("\n");
	testRemoveLeftMost();

	printf("\n");
	testRemoveNode();


	return 0;


}

#endif
