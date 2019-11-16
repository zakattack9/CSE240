#include "employee.h"
#ifndef _IT_H_
#define _IT_H_
// Q1b: Create Noble class (5 points)
// Part 1: Create a child class of the Employee class named 'IT'
class IT : public Employee {
  public:
    IT(string employeeName, int noOfYears, departmentType deptType) : Employee(employeeName, noOfYears, deptType){};
    
    virtual void displayEmployee();
};

// Part2: Declare constructor which accepts the same 3 parameters as the parent class Employee's constructor.
// Pass the 3 parameters to the super constructor of the Employee class.


// Part 3: Re-declare the method displayEmployee (virtual method found inside of parent class Employee)

#endif // _IT_H_