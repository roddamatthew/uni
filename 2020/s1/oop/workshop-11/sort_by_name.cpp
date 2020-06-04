#include "animal.h"
#include "hunter.h"
#include "vegie.h"
#include "zoo.h"
#include "sort_by_name.h"
#include <algorithm>

bool compareName(animal* a, animal* b){
	return a -> get_name() < b -> get_name();
}


void sort_by_name::sort(animal **animals,int n){
	std::sort(animals, animals + n, compareName);
}