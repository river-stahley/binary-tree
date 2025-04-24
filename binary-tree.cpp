//***************************************************************************************
//	DESCRIPTION:	Program implements storing a list of integers, found in text files,
//					into a binary tree
//	DESIGNER:		River Stahley
//	FUNCTIONS:		main - Initiates program & calls CreateTree, OpenFiles & DestroyTree
//					OpenFiles - opens and validates text files
//					ReadFiles - upon validation, reads text file data into binary tree
//					Menu - calls MenuSelect, ValidateSelect & ProcessSelect
//					MenuSelect - displays menu and prompts user for a selection
//					ValidateSelect - validates menu choice
//					ProcessSelect - processes menu choice
//					CreateTree - allocates and initializes a new binary tree
//					IsEmpty - determines whether the tree is empty or not
//					CreateNode - allocates and fills a new node
//					InsertNode - inserts a new node into the tree
//					FindNode - searches for a value in the tree
//					DeleteNode - deletes a node from the tree
//					InOrderDisplay - displays all integers in tree (recursive in-order)
//					FreeNodes - recursively de-allocates all memory from the tree
//					DestroyTree - de-allocates all nodes from the tree
//***************************************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include <string>


using namespace std;

// node structure

struct node
{
	int num;
	node *left;
	node *right;
};

// binary tree structure

struct binaryTree
{
	int count;
	node *root;
};

// prototypes

int OpenFiles (binaryTree *newTree, string& filename);	
int ReadFiles (binaryTree *newTree, string& filename);
int Menu (binaryTree* newTree);
void MenuSelect (char& selection);
bool ValidateSelect (char& selection);
bool ValidateNum (int& num);
void ProcessSelect (binaryTree *newTree, char& selection);
binaryTree* CreateTree();
bool IsEmpty (node* root);
node* CreateNode (int num); 
void InsertNode (binaryTree *newTree, int insertNum);
bool FindNode (binaryTree *newTree, int searchNum);
void DeleteNode (binaryTree *newTree);
void InOrderDisplay (node* root);
void FreeNodes (node* root);
void DestroyTree (binaryTree* newTree); 

//********************************************************************************
//  FUNCTION:	  main
//  DESCRIPTION:  Initiates program & calls 3 functions
//  INPUT:        Parameters: None
//  OUTPUT: 	  Return value: 0 indicating program exited successfully
//  CALLS TO:	  CreateTree, OpenFiles, DestroyTree
//*******************************************************************************

int main()
{
	string filename;	// data filename

	// call CreateTree
	
	binaryTree *searchTree = CreateTree();

	// call OpenFiles
	
	OpenFiles (searchTree, filename);
	
	// call DestroyTree
	
	DestroyTree (searchTree);
	
	return 0;
}

//*****************************************************************************
//  FUNCTION:	  OpenFiles
//  DESCRIPTION:  opens and validates text files
//  INPUT:        Parameters:	newTree - pointer to new binary tree
//								filename - data filename
//  OUTPUT: 	  Return value: 1 - if user chooses to exit program
//  CALLS TO:	  ReadFiles, Menu
//*****************************************************************************

int OpenFiles (binaryTree *newTree, string& filename)
{
	ifstream infile;	// for reading text file
	int cursor;		// position of the cursor
	int exit;		// early exit

	// prompt user for filename
	
	cout << "Enter a valid filename:" << " ";
	getline(cin, filename);
	
	// open file
	
	infile.open (filename.c_str());
	
	// loop until user enters a valid filename
	
	while (!infile)
	{
		cout << endl;
		cout << "Error - invalid input!" << endl << endl;
		cout << "Enter a valid filename:" << " ";
		getline (cin, filename);
	
		infile.open (filename.c_str());
	}
	
	// determine if file is empty
	
	infile.seekg (0, ios::end);
	cursor = infile.tellg();
	infile.close();
	
	// file is empty call Menu function
	
	if (cursor == 0)
	{
		// Display total number of integers in binary search tree

		cout << endl;
		cout << "There are " << newTree->count << " integers in the binary search tree." << endl;
		
		// call Menu function
		
		int exit = Menu (newTree);
		
		// if user chooses to exit
		// return 1 to main
		
		if (exit == 1)
		{
			return 1;
		}
	}
	
	// file is not empty call ReadFiles function
	
	if (cursor > 0)
	{
		int readFiles = ReadFiles (newTree, filename);
	}
}

//*****************************************************************************
//  FUNCTION:	  ReadFiles
//  DESCRIPTION:  upon validation, reads text file data into binary tree
//  INPUT:        Parameters:	newTree - pointer to new binary tree
//								filename - data filename
//  OUTPUT: 	  Return value: 1 - if user chooses to exit
//  CALLS TO:	  Menu, InsertNode
//*****************************************************************************

int ReadFiles (binaryTree* newTree, string& filename)
{
	ifstream infile;	// for reading text file
	int num;	// integer stored in text file
	
	// text file is not empty re-open file
	 
	infile.open (filename.c_str());
	
	// insert unique integers into binary tree
	// call InsertNode
		
	while (infile >> num)
	{
		InsertNode (newTree, num);
	}
	
	// close text file
	
	infile.close();
	
	// Display total number of integers in binary search tree
	
	cout << endl;
	cout << "There are " << newTree->count << " integers in the binary search tree." << endl;
	
	// call Menu function
	
	int exit = Menu (newTree);
	
	// if user chooses to exit 
	// return 1 to main
	
	if (exit == 1)
	{
		return 1;
	}
}

//*****************************************************************************
//  FUNCTION:	  Menu
//  DESCRIPTION:  Processes Menu selection by calling 3 functions to: 
//				  1) Display Menu 
//				  2) Validate Menu Choice 
//				  3) Process Menu Choice
//  INPUT:        Parameters:	newTree - pointer to new binary tree	
//  OUTPUT: 	  Return value: 1 - if user chooses to exit
//  CALLS TO:	  MenuSelect, ValidateSelect, ProcessSelect
//*****************************************************************************

int Menu (binaryTree *newTree)
{
	char choice;		// menu selection
	bool valid = false,		// for call to ValidateSelect
		 runProg = true; 	// menu flag
		
	while (runProg)
	{
		// call MenuSelect
		
		MenuSelect (choice);
		
		// if user choices 'E' return 1
		
		if (choice == 'E') 
		{
			cout << endl;
			cout << "Exiting program!" << endl << endl;
			system ("PAUSE");
			runProg = false;
			return 1;
		}
		
		else
		{
			// call ValidateSelect
			
			valid = ValidateSelect (choice);
			
			// if valid call ProcessSelect
			
			if (valid)
			{
				ProcessSelect (newTree, choice);
			}
		}
	}
}

//*****************************************************************************
//  FUNCTION:	  MenuSelect
//  DESCRIPTION:  displays menu and prompts user for a selection
//  INPUT:        Parameters:	selection - menu selection
//  OUTPUT: 	  Return value: none
//  CALLS TO:	  none
//*****************************************************************************

void MenuSelect (char& selection)
{
	char choice;	// menu choice
	bool valid;		// for menu choice validation
	
	while (!valid)
	{
		// Display sort menu
		
		cout << endl;
		cout << "Binary Search Tree Menu:" << endl;
		cout << setw(36) << "A = Add An Integer to the Tree" << endl;
		cout << setw(41) << "D = Delete An Integer from the Tree" << endl;
		cout << setw(44) << "P = Print Out All Integers in the Tree" << endl;
		cout << setw(43) << "S = Search for an Integer in the Tree" << endl;
		cout << setw(22) << "E = Exit Program" << endl;
		
		// prompt user for menu selection
		
		cout << endl;
		cout << "Enter a selection:" << " ";
		cin >> choice;
		
		// convert input to upper case
		
		selection = toupper(choice);
		valid = true;
	}
}

//*****************************************************************************
//  FUNCTION:	  ValidateSelect
//  DESCRIPTION:  validates menu choice
//  INPUT:        Parameters:	selection - menu selection
//  OUTPUT: 	  Return value: valid - true (valid input)
//									    false (invalid input)
//  CALLS TO:	  none
//*****************************************************************************

bool ValidateSelect (char& selection)
{
	bool valid = true;
	
	// invalid input - return false	
	
	if (!(selection == 'A' || selection == 'D' || selection == 'P'
			|| selection == 'S' || selection == 'E'))
	{
		cout << endl;
		cerr << "Error - invalid input!" << endl; 
		cerr << "Please enter an A, D, P, S, or E" << endl;
		valid = false;
	}
	
	return valid;
}

//*****************************************************************************
//  FUNCTION:	  ValidateNum
//  DESCRIPTION:  validates user inputted number
//  INPUT:        Parameters:	num - user input
//  OUTPUT: 	  Return value: valid - true (valid input)
//									    false (invalid input)
//  CALLS TO:	  none
//*****************************************************************************

bool ValidateNum (int& num)
{
	bool valid = true;
	
	// invalid input - return false	
	
	if (num <= 0)
	{
		cout << endl;
		cerr << "Error - invalid input!" << endl; 
		cerr << "Please enter a positive, non-zero integer" << endl;
		valid = false;
	}
	
	return valid;
}

//*******************************************************************************
//  FUNCTION:	  ProcessSelect
//  DESCRIPTION:  Processes menu choice
//  INPUT:        Parameters:	newTree - pointer to new binary tree
//								selection - menu selection
//  OUTPUT: 	  Return value: none
//  CALLS TO:	  InsertNode, FindNode, InOrderDisplay, DeleteNode, ValidateNum
//*******************************************************************************

void ProcessSelect (binaryTree *newTree, char& selection)
{
	bool found;		// call to FindNode
	bool valid;		// call to ValidateNum
	int num;		// user inputted integer
	
	// Selection - A (Add node to binary tree)
	
	if (selection == 'A')
	{
		// prompt user for integer to add
		
		cout << endl;
		cout << "Enter an integer to add to the binary tree:" << " ";
		cin >> num;
		
		// call ValidateNum
		
		valid = ValidateNum (num);
		
		// loop until input is valid
		
		while (!valid)
		{
			// prompt user for integer to add
		
			cout << endl;
			cout << "Enter an integer to add to the binary tree:" << " ";
			cin >> num;
			
			valid = ValidateNum (num);
		}
		
		// input is valid
		
		if (valid)
		{
			// call InsertNode
			
			InsertNode (newTree, num);
			
			// Display total number of integers in binary search tree
	
			cout << endl;
			cout << "There are " << newTree->count << " integers in the binary search tree." << endl;
		}
	}
	
	// Selection - D (Delete node from binary tree)
	
	else if (selection == 'D')
	{
		// call IsEmpty
		// root is NULL - return to menu
		
		if (IsEmpty(newTree->root))
		{
			cout << endl;
			cerr << "Cannot delete from an empty binary tree!" << endl;
			return;
		}
		
		// prompt user for integer to delete
		
		cout << endl;
		cout << "Enter an integer to delete from the binary tree:" << " ";
		cin >> num;
		
		// call ValidateNum
		
		valid = ValidateNum (num);
		
		// loop until input is valid
		
		while (!valid)
		{
			// prompt user for integer to add
		
			cout << endl;
			cout << "Enter an integer to add to the binary tree:" << " ";
			cin >> num;
			
			valid = ValidateNum (num);
		}
		
		// input is valid
		
		if (valid)
		{
			// call FindNode
			
			found = FindNode (newTree, num);
			
			// integer was not found - return to menu
			
			if (!found)
			{
				cout << endl;
				cerr << num << " was not found in binary tree!" << endl;
				return;
			}
			
			// call DeleteNode
			
			DeleteNode (newTree);
			
			// Display total number of integers in binary search tree
	
			cout << endl;
			cout << "There are " << newTree->count << " integers in the binary search tree." << endl;
		}
	}
	
	// Selection - P (Print all nodes from binary tree in-order)
	
	else if (selection == 'P')
	{
		// call IsEmpty
		// root is NULL - return to menu
		
		if (IsEmpty(newTree->root))
		{
			cout << endl;
			cerr << "Binary search tree is empty." << endl;
			return;
		}
		
		cout << endl;
		cout << "Values stored in binary search tree are:" << endl;
		
		// call InOrderDisplay
		
		InOrderDisplay (newTree->root);
		cout << endl;
	}
	
	// Selection - S (Search for integer in tree and display its subtree)
	
	else if (selection == 'S')
	{
		// call IsEmpty
		// root is NULL - return to menu
		
		if (IsEmpty(newTree->root))
		{
			cout << endl;
			cerr << "Cannot search an empty tree." << endl;
			return;
		}
		
		// prompt user for integer to find
		
		cout << endl;
		cout << "Enter an integer to find:" << " ";
		cin >> num;
		
		// call ValidateNum
		
		valid = ValidateNum (num);
		
		// loop until input is valid
		
		while (!valid)
		{
			// prompt user for integer to add
		
			cout << endl;
			cout << "Enter an integer to add to the binary tree:" << " ";
			cin >> num;
			
			valid = ValidateNum (num);
		}
		
		// input is valid
		
		if (valid)
		{
			// call FindNode
			
			found = FindNode (newTree, num);
			
			// integer was not found - return to menu
			
			if (!found)
			{
				cout << endl;
				cerr << num << " was not found in binary tree!" << endl;
				return;
			}
			
			// display subtree
			
			cout << endl;
			cout << "Values stored in subtree with root " << num << " are:" << endl;
		
			cout << setw(6) << newTree->root->left->num
			     << setw(6) << num << setw(6) << newTree->root->right->num;
			cout << endl;
		}
	}		
}

//*****************************************************************************
//  FUNCTION:	  CreateTree
//  DESCRIPTION:  allocates and initializes a new binary tree
//  INPUT:        Parameters:	none
//  OUTPUT: 	  Return value: newTree - pointer to new binary tree
//  CALLS TO:	  none
//*****************************************************************************

binaryTree* CreateTree()
{
	binaryTree *newTree = new binaryTree;	// pointer to new binary tree
	
	// memory allocation error
	
	if (newTree == NULL)
	{
		cout << endl;
		cerr << "ERROR -- Unable to allocate memory for binary search tree!" << endl;
	}
	
	// set count to zero and root pointer to NULL
	
	else
	{
		newTree->count = 0;
		newTree->root = NULL;
	}
	
	return newTree;
}

//*****************************************************************************
//  FUNCTION:	  IsEmpty
//  DESCRIPTION:  determines whether the tree is empty or not
//  INPUT:        Parameters:	root - pointer to root node
//  OUTPUT: 	  Return value: empty - true (if tree is empty)
//								   	    false (if tree is not empty)
//  CALLS TO:	  none
//*****************************************************************************

bool IsEmpty (node* root)
{
	bool empty = true;
	
	// root is not NULL - return false
	
	if (root != NULL)
	{
		empty = false;
	}
	
	return empty;
}

//*****************************************************************************
//  FUNCTION:	  CreateNode
//  DESCRIPTION:  allocates and fills a new node
//  INPUT:        Parameters:	num - integer value
//  OUTPUT: 	  Return value: newNode - pointer to new node
//								NULL - memory allocation failure
//  CALLS TO:	  none
//*****************************************************************************

node* CreateNode (int num)
{
	node *newNode = new node;	// pointer to new node
	
	// memory allocation failure
	
	if (newNode == NULL)
	{
		cout << endl;
		cerr << "ERROR - memory allocation failure!" << endl;
		return NULL;
	}
	
	// fill new node
	
	newNode->num = num;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return (newNode);
}

//*****************************************************************************
//  FUNCTION:	  InsertNode
//  DESCRIPTION:  inserts a new node into the tree
//  INPUT:        Parameters:	newTree - pointer to new binary tree
//								insertNum - integer being added	to tree
//  OUTPUT: 	  Return value: none
//  CALLS TO:	  CreateNode
//*****************************************************************************

void InsertNode (binaryTree *newTree, int insertNum)
{
	node* current;	// pointer to current node
	node* parent;	// pointer to parent node
	node* newNode;	// pointer to new node
	
	// call CreateNode
	
	newNode = CreateNode (insertNum);
	
	// empty binary tree
	// add new node
	
	if (newTree->root == NULL)
	{
		newTree->root = newNode;
		newTree->count++;
	}
	
	else
	{
		// traverse tree until appropriate
		// leaf position is found
		
		current = newTree->root;
		newTree->count++;
		
		while (current != NULL)
		{
			parent = current;
			
			// duplicate is found
			
			if (current->num == insertNum)
			{
				cout << endl;
				cerr << insertNum << " is already in the list ";
				cerr << "duplicates are not allowed." << endl;
				newTree->count--;
				return;	
			}
			
			else if (current->num > insertNum)
			{
				current = current->left;
			}
			
			else
			{
				current = current->right;
			}
		}
		
		// link the new child to its parent
		
		if (parent->num > insertNum)
		{
			parent->left = newNode;
		}
		
		else
		{
			parent->right = newNode;
		}
	}
}

//*****************************************************************************
//  FUNCTION:	  FindNode
//  DESCRIPTION:  searches for a value in the tree
//  INPUT:        Parameters:	newTree - pointer to new binary tree
//								searchNum - integer being searched for
//  OUTPUT: 	  Return value: found - true (if integer is found)
//									  - false (if integer is not found)
//  CALLS TO:	  none
//*****************************************************************************

bool FindNode (binaryTree *newTree, int searchNum)
{
	node *current;		// pointer to current node
	bool found = false;	// integer found or not found 
	
	// Error message displays if binary tree is empty
	
	if (newTree->root == NULL)
	{
		cout << endl;
		cerr << "Cannot search an empty tree." << endl;
	}
	
	else
	{
		current = newTree->root;
		
		while (current != NULL && !found)
		{
			// current->num == searchNum
			
			if (current->num == searchNum)
			{
				found = true;
			}
			
			// traverse current->left
			
			else if (current->num > searchNum)
			{
				current = current->left;
			}
			
			// traverse current->right
			
			else
			{
				current = current->right;
			}
		}
	}
	
	return found;
}

//*****************************************************************************
//  FUNCTION:	  DeleteNode
//  DESCRIPTION:  deletes a node from the tree
//  INPUT:        Parameters:	newTree - pointer to new binary tree	
//  OUTPUT: 	  Return value: none
//  CALLS TO:	  none
//*****************************************************************************

void DeleteNode (binaryTree* newTree)
{
	node *current;		// pointer to current node
	node *parent;		// pointer to parent node
	node* temp;			// pointer to node to be deleted
	
	// error messages displays - node is NULL
	
	if (newTree->root == NULL)
	{
		cout << endl;
		cerr << "Error: The node to be deleted is NULL." << endl;
		return;
	}
	
	// no leaf and right subtrees
	
	else if (newTree->root->left == NULL && newTree->root->right == NULL)
	{
		temp = newTree->root;
		temp = NULL;
		newTree->count--;
		delete temp;
		
	}
	
	// no leaf subtree
	
	else if (newTree->root->left == NULL)
	{
		temp = newTree->root;
		newTree->root = temp->right;
		newTree->count--;
		delete temp;
	}
	
	// no right subtree
	
	else if (newTree->root->right == NULL)
	{
		temp = newTree->root;
		newTree->root = temp->left;
		newTree->count--;
		delete temp;
	}
	
	// nonempty left and right subtrees
	
	else
	{
		current = newTree->root->left;
		parent = NULL;
		
		while (current->right != NULL)
		{
			parent = current;
			current = current->right;
		}
		
		newTree->root->num = current->num;
		
		if (parent == NULL)
		{
			newTree->root->left = current->left;
		}
		
		else
		{
			parent->right = current->left;
		}
		
		newTree->count--;
		
		delete current;
	}
}

//*****************************************************************************
//  FUNCTION:	  InOrderDisplay
//  DESCRIPTION:  displays all integers in tree (recursive in-order)
//  INPUT:        Parameters:	root - pointer to root node
//  OUTPUT: 	  Return value: none
//  CALLS TO:	  none
//*****************************************************************************

void InOrderDisplay (node* root)
{
	static int lastDisplayed = INT_MIN;

	if (root != NULL)
	{
		InOrderDisplay (root->left);
		
		cout << setw(7) << root->num << " ";
		lastDisplayed = root->num;
			
		InOrderDisplay (root->right);
	}	
}

//*****************************************************************************
//  FUNCTION:	  FreeNodes
//  DESCRIPTION:  recursively de-allocates all memory from the tree
//  INPUT:        Parameters:	root - pointer to root node
//  OUTPUT: 	  Return value: none
//  CALLS TO:	  none
//*****************************************************************************

void FreeNodes (node* root)
{
	if (root != NULL)
	{
		FreeNodes (root->left);
		FreeNodes (root->right);
		delete root;
		root = NULL;
	}
}

//*****************************************************************************
//  FUNCTION:	  DestroyTree
//  DESCRIPTION:  de-allocates all nodes from the tree
//  INPUT:        Parameters:	newTree - pointer to new binary tree 
//  OUTPUT: 	  Return value: none
//  CALLS TO:	  FreeNodes
//*****************************************************************************

void DestroyTree (binaryTree* newTree)
{
	FreeNodes (newTree->root);
}
