#include "Person.h"
#include "SortPerson.h"
#include <algorithm>

bool compareID(Person* a, Person* b){
	return a -> get_personID() < b -> get_personID();
}

void sort(Person **people, int n){
	std::sort(people, people + n, compareID);
}