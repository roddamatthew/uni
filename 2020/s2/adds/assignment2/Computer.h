#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

class ComputerPlayer
{
private:
	char move;
public:
	ComputerPlayer();
	char makeMove();
};
#endif //COMPUTER_H