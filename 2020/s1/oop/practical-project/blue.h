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
	void chase();
	void scatter();
	void eaten();
};
#endif //BLUE_H