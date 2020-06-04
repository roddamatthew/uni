#include "Person.h"
#include <string>

using namespace std;

	int Person::currentID = 0;

	Person::Person(){
		personID = currentID;
		currentID++;
	}

	Person::Person(string n, string o, int sl){
		name = n;
		occupation = o;
		serviceLength = sl;
		personID = currentID;
		currentID++;
	}

	void Person::set_name(string n){
		name = n;
	}

	string Person::get_name(){
		return name;
	}

	void Person::set_occupation(string o){
		occupation = o;
	}

	string Person::get_occupation(){
		return occupation;
	}

	void Person::set_salary(int s){
		if(s>0){
			salary = s;
		}
	}

	int Person::get_salary(){
		return salary;
	}

	void Person::set_serviceLength(int sl){
		serviceLength = sl;
	}

	int Person::get_serviceLength(){
		return serviceLength;
	}

	int Person::get_personID(){
		return personID;
	}