#ifndef ZOO_H
#define ZOO_H

#include "animal.h"
#include "vegie.h"
#include "hunter.h"

using namespace std;

class zoo
{
private:
	string name;
	int number_of_animals;
	animal** animals;
public:
	zoo(string n, int cows, int lions);
	void set_name(string n);
	string get_name();
	int get_number_of_animals();
	animal** get_animals();
};
#endif //ZOO_H