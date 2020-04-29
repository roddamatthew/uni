#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using namespace std;

class person
{
public:
	string name;
	int salary;

	person();

	person(string myName, int Salary); //Constructor taking a name and salary input parameters
	void setName(string myName);
	string getName();
	void setSalary(int mySalary);
	int getSalary();
};
#endif //PERSON_H