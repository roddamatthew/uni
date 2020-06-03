#ifndef HUNTER_H
#define HUNTER_H

#include <string>

using namespace std;

class Hunter:: public Animal
{
private:
	int kills;
	static int nextID;
public:
	Hunter(string n, int v);
};
#endif //HUNTER_H