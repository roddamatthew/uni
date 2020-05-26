#ifndef RED_H
#define RED_H

#include <iostream>
#include "entity.h"
#include "ghost.h"

using namespace std;

class Red: public Ghost
{

public:
	Red();
	void chase();
	void scatter();
	void eaten();
};
#endif //RED_H