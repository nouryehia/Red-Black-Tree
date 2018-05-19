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
	void iCase1(node*);
	void iCase2(node*);
	void iCase3(node*);
	void iCase4(node*);
	void iCase4_2(node*);
	void remove(int);
	void rCase1(node*);
	void rCase2(node*);
	void rCase3(node*);
	void rCase4(node*);
	void rCase5(node*);
	void rCase6(node*);
	void search(node*, int, bool&);
	void print(node*, int);
	bool isBlack(node*);
	bool isRed(node*);
	void rotateL(node*);
	void rotateR(node*);
	node* getGrandparent(node*);
	node* getSibling(node*);
	node* getUncle(node*);
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
	if (!toRepair->parent) iCase1(toRepair);
	else if (isBlack(toRepair->parent)) iCase2(toRepair);
	else if (getUncle(toRepair) && isRed(getUncle(toRepair))) iCase3(toRepair);
	else iCase4(toRepair);
}

//Node is root.
void tree::iCase1(node* n){
	if (!n->parent) n->color = black;
}

//Parent is black.
void tree::iCase2(node* n){
	return;
}

//Parent and uncle are red.
void tree::iCase3(node* n){
	n->parent->color = black;
	getUncle(n)->color = black;
	getGrandparent(n)->color = red;
	repair(getGrandparent(n));
}

//Parent is red and uncle is black.
void tree::iCase4(node* n){
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
	iCase4_2(n);
}

//Performs the second rotation needed to complete Case 4's repair.
void tree::iCase4_2(node* n){
	node* parent = n->parent;
	node* grandparent = getGrandparent(n);
	if (n == parent->left) rotateR(grandparent);
	else rotateL(grandparent);
	parent->color = black;
	grandparent->color = red;
}

//Removes a node from the tree.
void tree::remove(int data){
	node* toRemove = root;
	node* temp, *parent;

	//Search node.
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

	//If node has no children.
	if (!toRemove->left && !toRemove->right){
		if (!parent){
			delete toRemove;
			root = NULL;
		}
		else {
			if (isBlack(toRemove)) rCase1(toRemove);
			if (toRemove->data <= parent->data) parent->left = NULL;
			else parent->right = NULL;
			delete toRemove;
		}
	}

	//If node has right child.
	else if (!toRemove->left){
		if (isBlack(toRemove)){
			if (isRed(toRemove->right)) toRemove->right->color = black;
			else rCase1(toRemove);
		}
		if (!parent){
			temp = toRemove->right;
			temp->parent = NULL;
			root = temp;
		}
		else{
			if (toRemove->data <= parent->data) parent->left = toRemove->right;
			else parent->right = toRemove->right;
			toRemove->right->parent = parent;
		}
		delete toRemove;
	}

	//If node has left child.
	else if (!toRemove->right){
		if (isBlack(toRemove)){
			if (isRed(toRemove->left)) toRemove->left->color = black;
			else rCase1(toRemove);
		}
		if (!parent){
			temp = toRemove->left;
			root = temp;
		}
		else{
			if (toRemove->data <= parent->data) parent->left = toRemove->left;
			else parent->right = toRemove->left;
			toRemove->left->parent = parent;
		}
		delete toRemove;
	}

	//If node has two children.
	else {
		temp = toRemove->left;
		while (temp->right) temp = temp->right;
		toRemove->data = temp->data;
		if (isBlack(temp)){
			if (isRed(temp->left)) temp->left->color = black;
			else rCase1(temp);
		}
		if (temp->parent->left == temp){
			if (temp->left) {
				temp->parent->left = temp->left;
				temp->left->parent = temp->parent;
			}
			else temp->parent->left = NULL;
		}
		else {
			if (temp->left) {
				temp->parent->right = temp->left;
				temp->left->parent = temp->parent;
			}
			else temp->parent->right = NULL;
		}
		delete temp;
	}

	//Print tree.
	cout << "\nVisual representation of your tree after removal:\n";
	print(root, 0);
}

//Node is root.
void tree::rCase1(node* n){
	if (n->parent) rCase2(n);
}

//Sibling is red.
void tree::rCase2(node* n){
	node* sibling = getSibling(n);
	if (isRed(sibling)){
		n->parent->color = red;
		sibling->color = black;
		if (n == n->parent->left) rotateL(n->parent);
		else rotateR(n->parent);
	}
	rCase3(n);
}

//Parent, sibling, and sibling's children are black.
void tree::rCase3(node* n){
	node* sibling = getSibling(n);
	if (isBlack(n->parent) && isBlack(sibling) && (sibling && isBlack(sibling->left) && isBlack(sibling->right))){
		sibling->color = red;
		rCase1(n->parent);
	}
	else rCase4(n);
}

//Prent is red, sibling and its children are black.
void tree::rCase4(node* n){
	node* sibling = getSibling(n);
	if (isRed(n->parent) && isBlack(sibling) && isBlack(sibling->left) && isBlack(sibling->right)){
		sibling->color = red;
		n->parent->color = black;
	}
	else rCase5(n);
}

//Node is the left child of parent, sibling is black, sibling's left child is red, sibling's right child is black.
void tree::rCase5(node* n){
	node* sibling = getSibling(n);
	if (isBlack(sibling)){
		if (n == n->parent->left && (sibling && isBlack(sibling->right) && isRed(sibling->left))){
			sibling->color = red;
			sibling->left->color = black;
			rotateR(sibling);
		}
		else if (n == n->parent->right && (sibling && isBlack(sibling->left) && isRed(sibling->right))){
			sibling->color = red;
			sibling->right->color = black;
			rotateL(sibling);
		}
	}
	rCase6(n);
}

//Node is teh left child of parent, sibling is black, sibling's right child is red.
void tree::rCase6(node* n){
	node* sibling = getSibling(n);
	sibling->color = n->parent->color;
	n->parent->color = black;
	if (n == n->parent->left){
		sibling->right->color = black;
		rotateL(n->parent);
	}
	else {
		sibling->left->color = black;
		rotateR(n->parent);
	}
}

//Search a node in the tree.
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
		if (isBlack(n)) cout << n->data << " B";
		else cout << n->data << " R";
		print(n->left, space);
	}
	else cout << "\nTree is empty!";
}

//Returns if a node is black.
bool tree::isBlack(node* n){
	if (!n || n->color == black) return true;
	else return false;
}

//Returns if a node is red.
bool tree::isRed(node* n){
	if (n && n->color == red) return true;
	else return false;
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
	else root = newNode;
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
	else root = newNode;
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

#endif