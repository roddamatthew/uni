#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

class Computer
{
private:
	std::string name;
	char move;
public:
	Computer(std::string Name);
	char makeMove();
	std::string getName();
};
#endif //COMPUTER_H