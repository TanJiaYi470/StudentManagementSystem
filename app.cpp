#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<iomanip>
#include	<string>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char*, BST*);
int menu();


int main() {
	int choice;
	BST tree;
	type student;


	do {
		int order, source;
		choice = menu();
		if (choice == 1)
		{
			const char* filename = "student.txt";
			readFile(filename, &tree);
		}
		if (choice == 2)
		{
			int height = tree.tree_height(tree.root);
			tree.deepestNodes(tree.root, 0, height);
			cout << endl;
		}
		if (choice == 3)
		{
			cout << "You want to display in (1 - Ascending form, 2- Descending form): ";
			cin >> order;
			cout << endl << endl;
			cout << "Where do you want to display the output (1 - Screen/ 2 - File): ";
			cin >> source;
			cout << endl;
			tree.display(order, source);
		}
		if (choice == 4)
		{
			BST tree2;
			int id;
			cout << "Please key in the student id = ";
			cin >> id;
			student.id = id;
			//tree2.CloneSubtree2(tree, student);
			if ((tree2.CloneSubtree(tree, student)) == true && tree2.root != NULL) {
				cout << endl << "BST" << endl;
				cout << "++++++++++++++++++++++++++++++++++++++" << endl;
				tree.preOrderPrint();
				cout << "sub tree" << endl;
				cout << "++++++++++++++++++++++++++++++++++++++" << endl;
				tree2.preOrderPrint();
			}
			else {
				cout << "Cannot clone subtree." << endl;
			}
		}
		if (choice == 5)
		{
			int height = tree.tree_height(tree.root);
			tree.printLevelNodes(height);
		}
		if (choice == 6)
		{
			tree.printpath();
		}
		if (choice == 7)
		{
			system("cls");
			return 0;
		}
		system("pause");
		system("cls");
	} while (choice != 7);

	system("pause");
	return 0;
}

bool readFile(const char* filename, BST* bst)
{
	type student;
	BST tree;
	string ignore;
	int i = 0;

	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << "Failed to open " << filename << " file" << endl;
		return false;
	}
	else {
		while (!inFile.eof())
		{
			getline(inFile, ignore, '=');
			inFile >> student.id;

			//student name
			getline(inFile, ignore, '=');
			inFile.getline(student.name, sizeof(student.name));

			//student address
			getline(inFile, ignore, '=');
			inFile.getline(student.address, sizeof(student.address));

			//student DOB
			getline(inFile, ignore, '=');
			inFile.getline(student.DOB, sizeof(student.DOB));

			//student phone number
			getline(inFile, ignore, '=');
			inFile.getline(student.phone_no, sizeof(student.phone_no));

			//student course
			getline(inFile, ignore, '=');
			inFile.getline(student.course, sizeof(student.course));

			//student CGPA
			getline(inFile, ignore, '=');
			inFile >> student.cgpa;

			tree.insert(student);
			i++;
			*bst = tree;
		}
		inFile.close();

		cout << i << " of student records successfully read." << endl;
		return true;
	}
}

int menu()
{
	int choice;
	cout << "(1) Read data to BST" << endl;
	cout << "(2) Print deepest nodes" << endl;
	cout << "(3) Display student " << endl;
	cout << "(4) Clone Subtree" << endl;
	cout << "(5) Print Level Nodes" << endl;
	cout << "(6) Print Path" << endl;
	cout << "(7) Exit" << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	while (choice < 1 || choice > 7) {
		cout << "Invalid choice. Please select a number between 1 to 7" << endl;
		cout << "Please enter your choice again: ";
		cin >> choice;
		system("cls");
	}
	system("cls");
	return choice;
}
