#ifndef MARKET_H
#define MARKET_H

#include <string>
#include <iostream>

using namespace std;

class Market
{
public:
	string name;
	int age;

	Market();
	void setName(string marName);
	string getName();

	void setAge(int marAge);
	int getAge();

};
#endif //MARKET_H