#ifndef TRUCKLOADS_H
#define TRUCKLOADS_H

class TruckLoads
{
private:
	int numTrucksHelper(int numCrates, int loadSize);
public:
	TruckLoads();
	int numTrucks(int numCrates, int loadSize);
};
#endif //TRUCKLOADS