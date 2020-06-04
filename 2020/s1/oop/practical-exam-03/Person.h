#ifndef PERSON_H
#define PERSON_H

using namespace std;

#include <string>

class Person
{
protected:
	string name;                       // the name of a person
 	string occupation;                 // the occupation of a person
 	int salary;                        // the salary of a person; takes only non-negative values
 	int serviceLength;                   // the service length of a person
 	int personID;                        // the unique ID of a person
 	static int currentID;

public:
	Person();
	Person(string n, string o, int sl);

	void set_name(string n);
	string get_name();

	void set_occupation(string o);
	string get_occupation();

	void set_salary(int s);
	virtual int get_salary() = 0;

	void set_serviceLength(int sl);
	int get_serviceLength();

	int get_personID();
};
#endif //PERSON_H