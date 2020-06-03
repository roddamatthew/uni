#ifndef VEGIE_H
#define VEGIE_H

using namespace std;

#include <string>
#include "animal.h"

class vegie: public animal
{
private:
	string favourite_food;
	static int nextID;
public:
	vegie(string n, int v);
	void set_favourite_food(string n);
	string get_favourite_food();
	string get_name();
};
#endif //VEGIE_h