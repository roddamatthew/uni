#ifndef COACH_H
#define COACH_H

#include "Person.h"
#include <string>

using namespace std;

class Coach: public Person
{
private:
	static int nextID;
public:
	Coach(string n, int sl);
	int get_salary();
};
#endif //COACH_H