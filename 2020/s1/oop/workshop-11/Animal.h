#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

using namespace std;

class Animal
{
private:
	string name ;
	int animalID ;
	int volume ;
	static int currentID;
public:
	Animal(string n, int v);
	void set_name(string n);
	string get_name();
	void set_volume(int v);
	int get_volume();
	int get_animalID();
};
#endif //ANIMAL_H