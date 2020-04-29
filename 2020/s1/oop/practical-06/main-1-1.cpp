#include <iostream>
#include "meerkat.h"

using namespace std;

int main(){
	meerkat *A, *B;

	string nameA, nameB;
	int ageA, ageB;
	int salaryC, salaryD;

	A = new meerkat();
	A -> setName("A");
	A -> setAge(1);

	nameA=A -> getName();
	ageA=A -> getAge();

	B = new meerkat();
	B -> setName("B");
	B -> setAge(2);

	nameB=B -> getName();
	ageB=B -> getAge();

	std::cout << nameA << std::endl;
	std::cout << ageA << std::endl;
	std::cout << nameB << std::endl;
	std::cout << ageB << std::endl;

	return 0;

}