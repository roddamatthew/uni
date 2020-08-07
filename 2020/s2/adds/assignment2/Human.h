#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>

class HumanPlayer
{
private:
	std::vector<char> moves;
public:
	HumanPlayer();
	char makeMove();
};
#endif //HUMAN_H