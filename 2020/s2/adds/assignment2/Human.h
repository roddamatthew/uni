#ifndef HUMAN_H
#define HUMAN_H

#include <string>

class HumanPlayer
{
private:
	std::string name;
	char move;
public:
	HumanPlayer(std::string Name);
	char makeMove();
	std::string getName();
};
#endif //HUMAN_H