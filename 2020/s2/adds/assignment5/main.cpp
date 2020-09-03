#include "MapGeneric.h"
#include "MapTriple.h"
#include "MapSquare.h"
#include "MapAbsoluteValue.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	MapTriple MT;
	MapSquare MS;
	MapAbsoluteValue MA;

	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;


	for(int i = 0; i < 20; i++)
	{
		v1.push_back( -i ) ;
	}

	v2 = MT.map( v1 );
	v3 = MS.map( v1 );
	v4 = MA.map( v1 );

	for(int i = 0; i < 20; i++)
	{
		std::cout << "V = " << v1[i] << "	" << "Triple = " << v2[i] << "	" << "Square = " << v3[i] << "	Absolute = " << v4[i] << std::endl;
	}

	return 0;
}