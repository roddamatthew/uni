#ifndef MEERKAT_H
#define MEERKAT_H

#include <string>
#include <iostream>

using namespace std;

class meerkat
{
public: 
	meerkat(); //Default constructor
	
	string name;
	int age;

	void setName(string meerName); //Change the meerkat's name
	string getName(); //Output meerkat's name
	void setAge(int meerAge); //Set the meerkat's age
	int getAge(); //Output the meerkat's age

	~meerkat();

};
#endif //MEERKAT_H