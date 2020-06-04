#include "animal.h"
#include "hunter.h"
#include "vegie.h"
#include "zoo.h"
#include "sort_by_animalID.h"
#include <algorithm>

bool compareID(animal* a, animal* b){
	return a -> get_animalID() < b -> get_animalID();
}

void sort_by_animalID::sort(animal** animals,int n){
	std::sort(animals, animals + n, compareID);
}