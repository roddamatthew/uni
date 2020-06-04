#include "Person.h"
#include "Coach.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
	Coach* matt = new Coach("Matt", 20);

	std::cout << "Coach named: " << matt -> get_name() << " has occupation: " << matt -> get_occupation();
	std::cout << " and has been doing that for: " << matt -> get_serviceLength() << " years." << std::endl;
	std::cout << "Coach has ID: " << matt-> get_personID() <<std::endl; 

	return 0;
}