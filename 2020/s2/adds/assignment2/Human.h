#ifndef HUMAN_H
#define HUMAN_H

#include <string>

class Human
{
private:
	std::string name;
	char move;
public:
	Human(std::string Name);
	char makeMove();
	std::string getName();
};
#endif //HUMAN_H