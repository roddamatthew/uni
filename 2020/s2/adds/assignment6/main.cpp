#include "Individual.h"
#include "Mutator.h"
#include "BitFlip.h"
#include "BitFlipProb.h"
#include "Rearrange.h"

#include <iostream>
#include <string>

extern Individual * execute(Individual * indPtr, Mutator * mPtr, int k) ;

using namespace std;

int main(){
	string binarystr1 ;
	int k1 ;
	string binarystr2 ;
	int k2 ;

	std::cin >> binarystr1 ;
	std::cin >> k1 ;
	std::cin >> binarystr1 ;
	std::cin >> k2 ;

	// Individual *  DNA1 = new Individual( binarystr1 ) ;
	// Individual *  DNA2 = new Individual( binarystr2 ) ;

	// BitFlip * BF = new BitFlip() ;
	// Rearrange * R = new Rearrange() ;

	// Individual * aptr = execute( DNA1, BF, k1 ) ;
	// Individual * aptr2 = execute( aptr, R, k1 ) ;

	// //Individual * bptr = execute( &DNA2, BF, k2 ) ;
	// //Individual * bptr2 = execute( bptr, R, k2 ) ;


	// std::cout << aptr2 -> getString() << std::endl;//<< bptr -> getString() << bptr -> getMaxOnes() << std::endl ;

	return 0 ;
}

Individual * execute(Individual * indPtr, Mutator * mPtr, int k)
{
	Individual ind ;

	ind = mPtr -> mutate( *indPtr, k ) ;

	Individual* indptr = &ind ;
	
	return indptr ;
}