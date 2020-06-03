#ifndef HUNTER_H
#define HUNTER_H

#include <string>
#include "animal.h"

using namespace std;

class hunter: public animal
{
private:
	int kills;
	static int nextID;
public:
	hunter(string n, int v);
	void set_kills(int n);
	int get_kills();
	string get_name();
};
#endif //HUNTER_H