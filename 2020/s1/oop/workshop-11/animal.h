#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

using namespace std;

class animal
{
protected:
	string name ;
	int animalID ;
	int volume ;
	static int currentID;
public:
	animal(string n, int v);
	animal();
	void set_name(string n);
	virtual string get_name();
	void set_volume(int v);
	int get_volume();
	int get_animalID();
};
#endif //ANIMAL_H