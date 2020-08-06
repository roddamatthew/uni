#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

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
#endif //COMPUTERPLAYER_H