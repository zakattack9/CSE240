#include <iostream>
#include <string>
#include "it.h"

// Q2b: Define displayEmployee() for IT class (5 points)
// Define the function displayEmployee() that you declared within the IT class in the header file
// See expected output in question file.
void IT::displayEmployee() {
  string department = Employee::getDepartmentType() == 0 ? "HR" : "IT";
  cout << "\nEmployee name: " << Employee::getName() << endl;
  cout << "Years: " << Employee::getYears() << endl;
  cout << "Department: " << department << endl;
}

// (displayList() function in hw9.cpp should call this function.)
// Include necessary header files


