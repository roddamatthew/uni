#ifndef BLUE_H
#define BLUE_H

#include <iostream>
#include "entity.h"
#include "ghost.h"

using namespace std;

class Blue: public Ghost
{

public:
	Blue();
	void chase(int pacRow, int pacColumn, char pacLastDirection, int redRow, int redColumn);
	void scatter();
	void eaten();
};
#endif //BLUE_H