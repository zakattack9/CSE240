
// CSE240 Fall 2019 HW6
// Zak Sakata
// Write the compiler used: GCC

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of employee records.
// Each record(struct) has this information: employee's name, supervisor's name, department of the employee, room number.
// The struct 'employeeRecord' holds information of one employee. Department is enum type.
// A linked list called 'list' is made to hold the list of employees.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// You should not modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.
// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. 10% deduction for not using comments *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996) // for Visual Studio Only

#define MAX_NAME_LENGTH 25

typedef enum
{
	HR = 0,
	Marketing,
	IT
} departmentType; // enum type

struct employeeRecord
{
	char employeeName[MAX_NAME_LENGTH];
	char supervisorName[MAX_NAME_LENGTH];
	departmentType department;
	unsigned int roomNumber;
	struct employeeRecord *next; // pointer to next node
} *list = NULL;								 // Declare linked list 'list'

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:
int add(char *employeeName_input, char *supervisorName_input, char *department_input, unsigned int roomNumber_input); // 10 points
void displayList();																																																		// 10 points
int countNodes();																																																			// 5 points
int deleteNode(char *employeeName_input);																																							// 10 points
void swapNodes(struct employeeRecord *node1, struct employeeRecord *node2);																						// 5 points
void sortList();																																																			// 10 points

int main()
{
	char selection = 'i'; // initialized to a dummy value
	printf("\nCSE240 HW6\n");
	do
	{
		printf("\nCurrently %d employee(s) on the list.", countNodes()); // NOTE: countNodes() called here
		printf("\nEnter your selection:\n");
		printf("\t a: add a new employee\n");
		printf("\t d: display employee list\n");
		printf("\t r: remove a employee from the list\n");
		printf("\t s: sort employee list by supervisor's name in descending order\n");
		printf("\t q: quit\n");
		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do
		c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the code in the function, case by case
void executeAction(char c)
{
	char employeeName_input[MAX_NAME_LENGTH], supervisorName_input[MAX_NAME_LENGTH];
	unsigned int roomNumber_input, result = 0;
	char department_input[20];
	switch (c)
	{
	case 'a': // add employee
		// input employee details from user
		printf("\nEnter employee name: ");
		fgets(employeeName_input, sizeof(employeeName_input), stdin);
		employeeName_input[strlen(employeeName_input) - 1] = '\0'; // discard the trailing '\n' char
		printf("Enter supervisor name: ");
		fgets(supervisorName_input, sizeof(supervisorName_input), stdin);
		supervisorName_input[strlen(supervisorName_input) - 1] = '\0'; // discard the trailing '\n' char

		printf("Enter whether employee is in 'HR' or 'Marketing' or 'IT': ");
		fgets(department_input, sizeof(department_input), stdin);
		department_input[strlen(department_input) - 1] = '\0'; // discard the trailing '\n' char
		printf("Please enter room number: ");
		scanf("%d", &roomNumber_input);
		flushStdIn();

		// add the employee to the list
		result = add(employeeName_input, supervisorName_input, department_input, roomNumber_input);
		if (result == 0)
			printf("\nEmployee is already on the list! \n\n");
		else if (result == 1)
			printf("\nEmployee successfully added to the list! \n\n");

		break;

	case 'd': // display the list
		displayList();
		break;

	case 'r': // remove a employee
		printf("\nPlease enter employee name: ");
		fgets(employeeName_input, sizeof(employeeName_input), stdin);
		employeeName_input[strlen(employeeName_input) - 1] = '\0'; // discard the trailing '\n' char

		// delete the node
		result = deleteNode(employeeName_input);
		if (result == 0)
			printf("\nEmployee does not exist! \n\n");
		else if (result == 1)
			printf("\nEmployee successfully removed from the list. \n\n");
		else
			printf("\nList is empty! \n\n");
		break;

	case 's': // sort the list
		sortList();
		break;

	case 'q': // quit
		break;
	default:
		printf("%c is invalid input!\n", c);
	}
}

// Q1 : add (10 points)
// This function is used to insert a new employee into the list. You can insert the new employee to the end of the linked list.
// Do not allow the employee to be added to the list if that employee already exists in the list. You can do that by checking the names of the employees already in the list.
// If the employee already exists then return 0 without adding employee to the list. If the employee does not exist in the list then go on to add the employee at the end of the list and return 1.
// NOTE: You must convert the string 'department_input' to an enum type and store it in the list because the struct has enum type for department.

int add(char *employeeName_input, char *supervisorName_input, char *department_input, unsigned int roomNumber_input) // 20 points
{
	struct employeeRecord *tempList = list; // work on a copy of 'list'
	struct employeeRecord *lastEmployee;

	// search for employee name already in linked list
	while (tempList != 0)
	{
		if (strcmp(employeeName_input, tempList->employeeName) == 0)
		{
			return 0;
		}
		else
		{
			lastEmployee = tempList;
			tempList = tempList->next;
		}
	}

	// create new employeeRecord struct
	struct employeeRecord *newEmployee;
	newEmployee = malloc(sizeof(struct employeeRecord));

	// convert department_input to enum
	departmentType departmentInput;
	if (strcasecmp(department_input, "HR") == 0)
	{
		departmentInput = HR;
	}
	else if (strcasecmp(department_input, "Marketing") == 0)
	{
		departmentInput = Marketing;
	}
	else if (strcasecmp(department_input, "IT") == 0)
	{
		departmentInput = IT;
	}

	// populate newEmployee struct with passed in param values
	strcpy(newEmployee->employeeName, employeeName_input);
	strcpy(newEmployee->supervisorName, supervisorName_input);
	newEmployee->department = departmentInput;
	newEmployee->roomNumber = roomNumber_input;
	newEmployee->next = NULL;

	// sets employeeRecord to head if no employees already exist in list
	if (list == NULL)
	{
		list = newEmployee;
	}
	else
	{
		// tempList is already at end of linked list after searching through prior
		lastEmployee->next = newEmployee;
	}

	return 1;
}

// Q2 : displayList (10 points)
// This function displays the linked list of employees, with all details (struct elements).
// Parse through the linked list and print the employee details one after the other. See expected output screenshots in homework question file.
// NOTE: Department is stored in the struct as enum type. You need to display a string for department.
void displayList()
{
	struct employeeRecord *tempList = list; // work on a copy of 'list'

	while (tempList != 0)
	{
		char *departmentStr;
		switch (tempList->department)
		{
		case HR:
			departmentStr = "HR";
			break;
		case Marketing:
			departmentStr = "Marketing";
			break;
		case IT:
			departmentStr = "IT";
			break;
		}

		printf("\nEmployee name: %s", tempList->employeeName);
		printf("\nSupervisor name: %s", tempList->supervisorName);
		printf("\nDepartment: %s", departmentStr);
		printf("\nRoom number: %d\n", tempList->roomNumber);

		tempList = tempList->next;
	}
}

// Q3: countNodes (5 points)
// This function counts the number of employees on the linked list and returns the number.
// You may use this function in other functions like deleteNode(), sortList(), addNode(), if needed.
// It can helpful to call this function in other functions, but not necessary.
// This function is called in main() to display number of employees along with the user menu.
int countNodes()
{
	int count = 0;
	struct employeeRecord *tempList = list;
	while (tempList != 0)
	{
		count++;
		tempList = tempList->next;
	}
	return count;
}

// Q4 : deleteNode (10 points)
// This function deletes the node specified by the employee name.
// Parse through the linked list and remove the node containing this employee name.
// NOTE: After you remove the node, make sure that your linked list is not broken.
// (Hint: Visualize the list as: list......-> node1 -> node_to_remove -> node2 -> ...end.
//        After removing "node_to_remove", the list is broken into "list ....node1" and "node2.... end". Stitch these lists.)

int deleteNode(char *employeeName_input)
{
	struct employeeRecord *tempList = list->next; // work on a copy of 'list'
	struct employeeRecord *deletedNode;
	struct employeeRecord *previousNode = list;

	// handles deletion of the first node of linked list
	if (strcmp(employeeName_input, list->employeeName) == 0)
	{
		deletedNode = list;
		list = tempList;
		free(deletedNode);
		return 1;
	}

	while (tempList != 0)
	{
		if (strcmp(employeeName_input, tempList->employeeName) == 0)
		{
			deletedNode = tempList;
			previousNode->next = tempList->next;
			free(deletedNode);
			return 1;
		}
		else
		{
			previousNode = tempList;
			tempList = tempList->next;
		}
	}

	return 0; // edit this line as needed
}

// Q5 : swapNodes (5 points)
// This function swaps the elements of parameters 'node1' and 'node2' (Here node1 does NOT mean 1st node of the list. 'node1' is just the name of the node)
// This function should not alter the 'next' element of the nodes. Only then will the nodes be swapped.
// Hint: The swap logic is similar to swapping two simple integer/string variables.
// NOTE: This function can be used in the sorting logic in sortList()

void swapNodes(struct employeeRecord *node1, struct employeeRecord *node2)
{
	struct employeeRecord *tempEmployee;
	tempEmployee = malloc(sizeof(struct employeeRecord));

	// copy node1's values to a temporary employee record
	strcpy(tempEmployee->employeeName, node1->employeeName);
	strcpy(tempEmployee->supervisorName, node1->supervisorName);
	tempEmployee->department = node1->department;
	tempEmployee->roomNumber = node1->roomNumber;

	// copy node2's values to node1
	strcpy(node1->employeeName, node2->employeeName);
	strcpy(node1->supervisorName, node2->supervisorName);
	node1->department = node2->department;
	node1->roomNumber = node2->roomNumber;

	// copy node1's values to node2
	strcpy(node2->employeeName, tempEmployee->employeeName);
	strcpy(node2->supervisorName, tempEmployee->supervisorName);
	node2->department = tempEmployee->department;
	node2->roomNumber = tempEmployee->roomNumber;
}

// Q6 : sortList (10 points)
// This function sorts the linked list by supervisor's name in descending order.
// Parse the list and compare the supervisor names to check which one should appear before the other in the list.
// Sorting should happen within the list. That is, you should not create a new linked list of employees having sorted employees.
// Hint: One of the string library function can be useful to implement this function because the sorting needs to happen by employee name which is a string.
//       Use swapNodes() to swap the nodes in the sorting logic

void sortList()
{
	struct employeeRecord *tempList = list; // work on a copy of 'list'
	int count = countNodes();

	for (int i = 0; i < count - 1; i++)
	{
		tempList = list;
		for (int j = 0; j < count - i - 1; j++)
		{
			if (strcmp(tempList->supervisorName, tempList->next->supervisorName) < 0)
			{
				swapNodes(tempList, tempList->next);
			}
			tempList = tempList->next;
		}
	}

	printf("\nEmployee list sorted! Use display option 'd' to view sorted list.\n");
}
