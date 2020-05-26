#ifndef PINK_H
#define PINK_H

#include <iostream>
#include "entity.h"
#include "ghost.h"

using namespace std;

class Pink: public Ghost
{

public:
	Pink();
	void chase();
	void scatter();
	void eaten();
};
#endif //PINK_H