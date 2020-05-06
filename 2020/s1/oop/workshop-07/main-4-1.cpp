#include <iostream>
#include "Market.h"

int main(){
	Market *market1;

	string marName;
	int marAge;

	market1 = new Market();
	std::cout << market1->getName() << market1->getAge() << std::endl;
	market1->setName("Farts");
	std::cout << market1->getName() << market1->getAge() << std::endl;
	market1->setAge(1204);
	std::cout << market1->getName() << market1->getAge() << std::endl;

	return 0;
}