#include "animal.h"
#include "hunter.h"
#include "vegie.h"
#include "zoo.h"
#include "sort_by_animalID.h"
#include <algorithm>

void sort_by_animalID::sort(animal** animals,int n){
	std::sort(animals, animals + n);
}