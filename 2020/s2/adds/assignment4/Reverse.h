#ifndef REVERSE_H
#define REVERSE_H

#include <string>

class Reverse
{
private:
	int reverseDigitHelper(int value, int reversed);
	std::string reverseStringHelper(std::string letters, std::string reversed);
public:
	Reverse();
	int reverseDigit(int value);
	std::string reverseString(std::string letters);
};
#endif //REVERSE_H
