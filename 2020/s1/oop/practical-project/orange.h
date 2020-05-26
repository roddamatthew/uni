#ifndef ORANGE_H
#define ORANGE_H

#include <iostream>
#include "entity.h"

using namespace std;

class Orange: public Ghost
{
public:
	Orange();
	void chase(int pacRow, int pacColumn);
	void scatter();
	void eaten();
};
#endif //ORANGE_H