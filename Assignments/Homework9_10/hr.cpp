#include <iostream>
#include <string>
#include "hr.h"

// Q2a: Define displayEmployee() for HR class (5 points)
// Define the function displayEmployee() that you declared within the HR class in the header file
// See expected output in question file.
void HR::displayEmployee() {
  string department = Employee::getDepartmentType() == 0 ? "HR" : "IT";
  cout << "\nEmployee name: " << Employee::getName() << endl;
  cout << "Years: " << Employee::getYears() << endl;
  cout << "Department: " << department << endl;
}

// (displayList() function in hw9.cpp should call this function.)
// Include necessary header files

