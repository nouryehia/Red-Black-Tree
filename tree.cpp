/* Red Black Tree
 * Author: Nour Yehia
 * Date: 4-30-18
 * This program creates a red black tree from a list of numbers and allows the user to search or remove a number in the tree.*/

//Includes.
#include "tree.h"
#include <fstream>
#include <stdlib.h>

//Declare functions.
void insert(tree&, char*);
void remove(tree);
void search(tree);
int parseCSV(char*, int*);


int main(){

	//Declare variables.
	tree tree;
	char answer[80];
	bool again = true;

	//Prompt user for first insertion (All other functions are useless if the tree is empty).
	cout << "\nThis program creates a red black tree from a list of numbers.\n";
	insert(tree, answer);
	
	//Ask the user what is to be done next.
	while (again){
		cout << "\n\nEnter 'I' if you would like to insert more numbers to your tree.\n"
			 << "Enter 'R' if you would like to search a number in your tree.\n"
			 << "Enter 'S' if you would like to remove a number from your tree.\n"
			 << "Enter 'Q' if you would like to quit the program.\n\n";
		cin >> answer;
		while (strcmp(answer, "I") != 0 && strcmp(answer, "i") != 0 
			   && strcmp(answer, "R") != 0 && strcmp(answer, "r") != 0
			   && strcmp(answer, "S") != 0 && strcmp(answer, "s") != 0 
			   && strcmp(answer, "Q") != 0 && strcmp(answer, "q") != 0){
			cout << "\nPlease enter 'I', 'S', 'R', or 'Q'.\n\n";
			cin >> answer;
		}
		if (strcmp(answer, "I") == 0 || strcmp(answer, "i") == 0) insert(tree, answer);
		else if (strcmp(answer, "R") == 0 || strcmp(answer, "r") == 0) remove(tree);
		else if (strcmp(answer, "S") == 0 || strcmp(answer, "s") == 0) search(tree);
		else if (strcmp(answer, "Q") == 0 || strcmp(answer, "q") == 0) again = false;
	}
}

//Prompts user for list and inserts every number in tree.
void insert(tree &tree, char* answer){

	int data[80], num;
	char list[800], fileName[80];

	//Prompt user to manually enter a list or to read a list from a file.
	while (strcmp(answer, "M") != 0 && strcmp(answer, "m") != 0 
		   && strcmp(answer, "F") != 0 && strcmp(answer, "f") != 0){
		cout << "\nEnter 'M' to manually enter a list.\n"
			 << "Enter 'F' to use a list from a file.\n\n";
		cin >> answer; 
	}

	//If user wants to manually enter a list...
	if (strcmp(answer, "M") == 0 || strcmp(answer, "m") == 0){

		//Prompt user for the list.
		cout << "\nEnter the list below. Make sure the numbers are separated by a comma.\n\n";
		cin >> list;
		int num = parseCSV(list, data);
		for (int i = 0; i < num; i++){
			tree.insert(data[i]);
		}
	}

	//If user wants to read a list from a file...
	else if (strcmp(answer, "F") == 0 || strcmp(answer, "f") == 0){
		ifstream inFile;

		//Prompt user for the name of the file.
		cout << "\nWhat is the name of the file you would like to read?\n\n";
		cin >> fileName;
		inFile.open(fileName);
		while (!inFile){
			cout << "\nFile not found. Retype the name of the file you would like to read.\n\n";
			cin >> fileName;
			inFile.open(fileName);
		}

		//Add elements from the list to the tree.
		inFile>>list;
		inFile.close();
		int num = parseCSV(list, data);
		for (int i = 0; i < num; i++){
			tree.insert(data[i]);
		}
	}

	//Print tree.
	cout << "\nVisual representation of your tree after insertion:\n";
	tree.print(tree.root, 0);
}

//Prompts user for a number to delete and removes it from the tree.
void remove(tree tree){
	cout << "\nThis function will be available soon (hopefully).";
	/*int data; 

	cout << "\nWhich number would you like to remove?\n\n";
	cin >> data;
	tree.remove(data);*/
}

//Prompts user for a number to search and return whether it is in the tree or not.
void search(tree tree){
	int data;

	bool found = false;
	cout << "\nWhich number would you like to search for?\n\n";
	cin >> data;
	tree.search(tree.root, data, found);
	if (!found) cout << endl << data << " is not in the tree.";

}

//Turns a list of numbers separated by commas into an int array with all the numbers. Returns the number of elements in the array. 
int parseCSV(char* list, int* data){
	char c, temp[8]; 
	int listIndex = 0, dataIndex = 0, pos = 0;

	while ((c=list[listIndex])!='\0'){
		if (c != ','){
			temp[pos] = c;
			pos++;
		}
		else{
			temp[pos] = '\0';
			data[dataIndex++] = atoi(temp);
			pos = 0;
		}
		listIndex++;
	}
	temp[pos] = '\0';
	data[dataIndex++] = atoi(temp);
	return dataIndex;
}