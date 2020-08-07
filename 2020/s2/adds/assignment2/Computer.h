#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

class ComputerPlayer
{
private:
	std::string name;
	char move;
public:
	ComputerPlayer(std::string Name);
	char makeMove();
	std::string getName();
};
#endif //COMPUTER_H