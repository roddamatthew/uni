#ifndef HUNTER_H
#define HUNTER_H

#include <string>

using namespace std;

class hunter:: public animal
{
private:
	int kills;
	static int nextID;
public:
	hunter(string n, int v);
};
#endif //HUNTER_H