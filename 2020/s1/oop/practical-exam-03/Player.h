#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"
#include <string>

using namespace std;

class Player: public Person
{
private:
	static int nextID;
	int games;
	int* gametime;

public:
	Player(string n, int sl, int *list, int m);
	int searchGame(int x);
	int get_salary();

};
#endif //PLAYER_H