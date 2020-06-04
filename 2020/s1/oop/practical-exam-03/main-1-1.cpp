#include "Person.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
	int i;
	Person* matt = new Person("Matt", "Programmer", 2);

	std::cout << "Person named: " << matt -> get_name() << " has occupation: " << matt -> get_occupation() << " and has been doing that for: " << matt -> get_serviceLength() << " years." << std::endl;


	return 0;
}