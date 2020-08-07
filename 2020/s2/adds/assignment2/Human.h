#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>

class HumanPlayer
{
private:
	std::vector<char> moves;
	int counter;
public:
	HumanPlayer();
	char makeMove();
	int getCounter();
};
#endif //HUMAN_H