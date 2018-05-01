/* Red Black Tree
 * Author: Nour Yehia
 * Date: 4-30-18
 * This program creates a red black tree from a list of numbers and allows the user to remove a number from the tree.*/

//Includes.
#include "tree.h"
#include <fstream>

int main(){

	//Declare variables.
	tree tree;
	int data, num;
	char answer[80], fileName[80];
	bool running = true;

	while (running){ 
		cout << "\nThis program creates a red black tree from a list of numbers.\n";

		//Prompt user to manually enter a list or to read a list from a file.
		while (strcmp(answer, "M") != 0 && strcmp(answer, "m") != 0 
			   && strcmp(answer, "F") != 0 && strcmp(answer, "f") != 0){
			cout << "\nEnter 'M' to manually enter a list.\n"
				 << "Enter 'F' to use a list from a file.\n\n";
			cin >> answer; 
		}

		//If user wants to manually enter a list...
		if (strcmp(answer, "M") == 0 || strcmp(answer, "m") == 0){

			//Prompt user to enter the number of elements in the list and to enter the list itself.
			cout << "\nHow many numbers do you want to add to your tree?\n\n";
			cin >> num;
			cout << "\nEnter the list below. Make sure the numbers are separated by a space.\n\n";
		
			//Add elements from the list to the tree.
			for (int i = 0; i < num; i++){
				cin >> data;
				tree.insert(data);
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
			while (inFile >> data) tree.insert(data);
			inFile.close();
		}

		//Print tree.
		cout << "\nVisual representation of your tree:\n";
		tree.print(tree.root, 0);
		
		//Prompt user to add more numbers.
		cout << "\n\nWould you like to add more numbers to your tree?\nEnter 'Y' if you do.\nEnter 'N' if you do not.\n\n";
		cin >> answer;
		while (strcmp(answer, "Y") != 0 && strcmp(answer, "y") != 0 
			   && strcmp(answer, "N") != 0 && strcmp(answer, "n") != 0){
			cout << "\nPlease enter 'Y' or 'N'.\n\n";
			cin >> answer;
		}
		if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0) running = false;
	}
}