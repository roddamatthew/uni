#ifndef PAC_H
#define PAC_H

#include <iostream>

using namespace std;

class Pac
{
private:
	int row;
	int column;

public:
	Pac(int rowstart, int columnstart);
	void movement(char direction);
	int getrow();
	int getcolumn();
};
#endif //PAC_H