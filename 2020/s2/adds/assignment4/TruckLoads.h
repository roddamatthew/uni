#ifndef TRUCKLOADS_H
#define TRUCKLOADS_H

class Truckloads
{
private:
	int numTrucksHelper(int numCrates, int loadSize);
public:
	Truckloads();
	int numTrucks(int numCrates, int loadSize);
};
#endif //TRUCKLOADS