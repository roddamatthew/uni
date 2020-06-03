#ifndef SORT_BY_ANIMALID
#define SORT_BY_ANIMALID

#include "animal.h"
#include "hunter.h"
#include "vegie.h"
#include "zoo.h"

class sort_by_animalID
{
public:
	static void sort(animal** animals,int n);	// sorts the array of n animals into ascending order using their animalIDs
};
#endif //SORT_BY_ANIMALID