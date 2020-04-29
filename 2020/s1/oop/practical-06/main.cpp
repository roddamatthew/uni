#include <iostream>
#include "meerkat.h"
#include "person.h"
#include "cart.h"

using namespace std;

int main(){
	meerkat *A, *B;
	person *C, *D;
	cart *E;

	string nameA, nameB, nameC, nameD;
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

	C = new person("oldC",400);
	C -> setName("C");
	C -> setSalary(500);

	nameC=C -> getName();
	salaryC=C -> getSalary();

	D = new person("oldD",800);
	D -> setName("D");
	D -> setSalary(1000);

	nameD=D -> getName();
	salaryD=D -> getSalary();

	E = new cart();
	E -> addMeerkat(*A);
	E -> addMeerkat(*B);
	E -> addMeerkat(*A);
	E -> addMeerkat(*B);

	E -> printMeerkats();


	std::cout << nameA << std::endl;
	std::cout << ageA << std::endl;
	std::cout << nameB << std::endl;
	std::cout << ageB << std::endl;
	std::cout << nameC << std::endl;
	std::cout << salaryC << std::endl;
	std::cout << nameD << std::endl;
	std::cout << salaryD << std::endl;


	return 0;

}