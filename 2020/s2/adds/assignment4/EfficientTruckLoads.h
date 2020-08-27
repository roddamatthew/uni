#ifndef EFFICIENT_TRUCKLOADS_H
#define EFFICIENT_TRUCKLOADS_H

#include <vector>

class EfficientTruckLoads
{
private:
	int** array;
	int index;
	int numTrucksHelper(int numCrates, int loadSize);
public:
	EfficientTruckLoads();
	int numTrucks(int numCrates, int loadSize);

};
#endif //EFFICIENT_TRUCKLOADS_H