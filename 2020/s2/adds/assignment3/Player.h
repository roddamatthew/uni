#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Player
{
protected:
	std::vector<char> moves;
	int counter;
public:
	Player();
	virtual char makeMove();
	int getCounter();
};
#endif //PLAYER_H