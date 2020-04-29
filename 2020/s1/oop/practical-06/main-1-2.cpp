#include <iostream>
#include "person.h"

using namespace std;

int main(){
	person *C, *D;

	string nameC, nameD;
	int salaryC, salaryD;

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

	std::cout << nameC << std::endl;
	std::cout << salaryC << std::endl;
	std::cout << nameD << std::endl;
	std::cout << salaryD << std::endl;


	return 0;

}