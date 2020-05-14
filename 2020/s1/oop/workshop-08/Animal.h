#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>

using namespace std;

class Animal
{
public:
	string species;
	string name;
	int id;
	static int currentID;

	Animal();

Animal(string aSpecies);       // animals are allocated a unique ID on creation, 
                                // the first animal has ID 1, the second animal is 2 and so on

void set_name(string aName);     // change the animal's name
string get_species();      
string get_name();
int get_ID();                    // the animal's unique ID
};
#endif //ANIMAL_H