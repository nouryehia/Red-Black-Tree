//Includes.
#include <iostream> 
#include <cstring>

using namespace std;

//If undefined.
#ifndef TREE_H 
#define TREE_H

//Variable that indicates a node's color.
enum color {red, black};

//Define class.
class tree {
protected:
	struct node{
		int data;
		color color;
		node *right, *left, *parent;
	};
public:
	node* root;
	tree();
	node* insert(int);
	void insertR(node*&, node*);
	void repair(node*);
	void case1(node*);
	void case2(node*);
	void case3(node*);
	void case4(node*);
	void case4_2(node*);
	void rotateL(node*);
	void rotateR(node*);
	node* getGrandparent(node*);
	node* getSibling(node*);
	node* getUncle(node*);
	void remove(int);
	void search(node*, int, bool&);
	void print(node*, int);
};

//Constructor.
tree::tree(){
	root = NULL;
}

//Non-recursive insert function (creates node and calls other functions). 
tree::node* tree::insert(int data){
	node* n = new node;
	n->data = data;
	n->color = red;
	n->parent = NULL;
	n->right = n->left = NULL;
	insertR(root, n);
	repair(n);
	root = n;
	while(root->parent) root = root->parent;
	return root;
}

//Recursive insert functions (adds new node to the tree without balancing it).
void tree::insertR(node* &head, node* toAdd){
	if (head && toAdd->data <= head->data) {
		if (head->left) insertR(head->left, toAdd);
		else {
			toAdd->parent = head;
			head->left = toAdd;
		} 
	} 
	else if (head) {
		if (head->right) insertR(head->right, toAdd);
		else {
			toAdd->parent = head;
			head->right = toAdd;
		}
	}
}

//Balances the tree by seeing which case applies to added node.
void tree::repair(node* toRepair){
	if (!toRepair->parent) case1(toRepair);
	else if (toRepair->parent->color == black) case2(toRepair);
	else if (getUncle(toRepair) && getUncle(toRepair)->color == red) case3(toRepair);
	else case4(toRepair);
}

//Node is root.
void tree::case1(node* n){
	if (!n->parent) n->color = black;
}

//Parent is black.
void tree::case2(node* n){
	return;
}

//Parent and uncle are red.
void tree::case3(node* n){
	n->parent->color = black;
	getUncle(n)->color = black;
	getGrandparent(n)->color = red;
	repair(getGrandparent(n));
}

//Parent is red and uncle is black.
void tree::case4(node* n){
	node* parent = n->parent;
	node* grandparent = getGrandparent(n);
	if (grandparent->left && grandparent->left->right && n == grandparent->left->right){
		rotateL(parent);
		n = n->left;
	}
	else if (grandparent && grandparent->right && grandparent->right->left && n == grandparent->right->left){
		rotateR(parent);
		n = n->right;
	}	
	case4_2(n);
}

//Performs the second rotation needed to complete Case 4's repair.
void tree::case4_2(node* n){
	node* parent = n->parent;
	node* grandparent = getGrandparent(n);
	if (n == parent->left) rotateR(grandparent);
	else rotateL(grandparent);
	parent->color = black;
	grandparent->color = red;
}

//Performs a left rotation.
void tree::rotateL(node* n){
	node* newNode = n->right;
	n->right = newNode->left;
	if (n->right) n->right->parent = n;
	newNode->left = n;
	newNode->parent = n->parent;
	if (n->parent) {
		if (n->parent->left == n) n->parent->left = newNode;
		else n->parent->right = newNode;
	}
	n->parent = newNode;
}

//Performs a right rotation.
void tree::rotateR(node* n){
	node* newNode = n->left;
	n->left = newNode->right;
	if (n->left) n->left->parent = n;
	newNode->right = n;
	newNode->parent = n->parent;
	if (n->parent){ 
		if (n->parent->left == n) n->parent->left = newNode;
		else n->parent->right = newNode;
	}
	n->parent = newNode;
}

//Returns a node's grandparent.
tree::node* tree::getGrandparent(node* n){
	node* parent = n->parent;
	if (!parent) return NULL;
	return parent->parent;
}

//Returns a node's sibling.
tree::node* tree::getSibling(node* n){
	node* parent = n->parent;
	if (!parent) return NULL;
	if (n == parent->left) return parent->right;
	else return parent->left;
}

//Returns a node's uncle.
tree::node* tree::getUncle(node* n){
	if (!getGrandparent(n)) return NULL;
	return getSibling(n->parent);
}

void tree::remove(int data){
	node* toRemove = root;
	node* temp, *parent;

	//Find node.
	if(!root){
		cout << "\nTree is empty. Add some numbers!.\n";
		return;
	}
	while (toRemove && toRemove->data != data){
		if (data < toRemove->data) toRemove = toRemove->left;
		else toRemove = toRemove->right;
	}
	if (!toRemove){
		cout << "\nNo node containing the number " << data << " was found in your tree.";
		return;
	}
	parent = toRemove->parent;

	//Delete node.
	if (!toRemove->left && !toRemove->right){
		if (!parent){
			delete toRemove;
			root = NULL;
		}
		else {
			if (toRemove->data <= parent->data) parent->left = NULL;
			else parent->right = NULL;
			delete toRemove;
		}
	}
	else if (!toRemove->left){
		if (!parent){
			temp = toRemove->right;
			delete toRemove;
			root = temp;
		}
		else{
			if (toRemove->data <= parent->data) parent->left = toRemove->right;
			else parent->right = toRemove->right;
			delete toRemove;
		}
	}
	else if (!toRemove->right){
		if (!parent){
			temp = toRemove->left;
			delete toRemove;
			root = temp;
		}
		else{
			if (toRemove->data <= parent->data) parent->left = toRemove->left;
			else parent->right = toRemove->left;
			delete toRemove;
		}
	}
	else {
		if (!parent || toRemove->data <= toRemove->parent->data){
			temp = toRemove->left;
			while (temp->right) temp = temp->right;
			toRemove->data = temp->data;
			if (temp->parent->left == temp){
				if (temp->left) temp->parent->left = temp->left;
				else temp->parent->left = NULL;
			}
			else{
				if (temp->left) temp->parent->right = temp->left;
				else temp->parent->right = NULL;	
			}
		}
		else {
			temp = toRemove->right;
			while (temp->left) temp = temp->left;
			toRemove->data = temp->data;
			if (temp->parent->right == temp){
				if (temp->right) temp->parent->right = temp->right;
				else temp->parent->right = NULL;
			}
			else{
				if (temp->right) temp->parent->left = temp->right;
				else temp->parent->left = NULL;
			}
		}
		delete temp;
	}

	cout << "\nVisual representation of your tree after removal:\n";
	print(root, 0);
}

void tree::search(node* n, int data, bool &found){
	if (!n) return;
	search(n->right, data, found);
	if (n->data == data) {
		found = true;
		cout << endl << n->data << " is in the tree.\n";
		if (n->parent) cout << "Parent: " << n->parent->data << endl;
		else cout << "Parent: NULL\n";
		if (getGrandparent(n)) cout << "Grandparent: " << getGrandparent(n)->data << endl;
		else cout << "Grandparent: NULL\n";
		if (getSibling(n)) cout << "Sibling: " << getSibling(n)->data << endl;
		else cout << "Sibling: NULL\n";
		if (getUncle(n)) cout << "Uncle: " << getUncle(n)->data;
		else cout << "Uncle: NULL";
		return;
	}
	search(n->left, data, found);
}

//Provides a visual representation of the tree. 
void tree::print(node* n, int space){
	if (root){
		int count = 6;
		if (!n) return;
		space += count;
		print(n->right, space);
		cout << endl;
		for (int i = count; i < space; i++) cout << " ";
		if (n->color == black) cout << n->data << " B";
		else cout << n->data << " R";
		print(n->left, space);
	}
	else cout << "\nTree is empty!";
}
#endif