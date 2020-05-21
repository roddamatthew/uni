#ifndef PAC_H
#define PAC_H

#include <iostream>

using namespace std;

class Pac
{
private:
	int x_pos;
	int y_pos;

public:
	Pac(int x, int y);
	void movement(char direction);
	int getx_pos();
	int gety_pos();
};
#endif //PAC_H