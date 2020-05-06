#include <iostream>
#include "Market.h"

using namespace std;

Market::Market(){
	name="?";
	age=0;
}

void Market::setName(string marName){
	name=marName;
}

string Market::getName(){
	return name;
}

void Market::setAge(int marAge){
	age=marAge;
}

int Market::getAge(){
	return age;
}