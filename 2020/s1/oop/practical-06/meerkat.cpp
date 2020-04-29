#include <iostream>
#include "meerkat.h"

using namespace std;

//Implementation of Meerkat constructor
meerkat::meerkat()
{
	name="?";
	age=0;
}

//Implementation of setName functionality
void meerkat::setName(string meerName)
{
	name=meerName;
}

// Implementation of setAge functionality
void meerkat::setAge(int meerAge)
{
	age=meerAge;
}

// Implementation of getName functionality
string meerkat::getName()
{
	return name;
}

// Implementation of getAge functionality
int meerkat::getAge()
{
	return age;
}

// Implementation of default destructor
meerkat::~meerkat()
{
}