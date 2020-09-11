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

	Individual a ( binarystr1 ) ;
	Individual b ( binarystr2 ) ;

	BitFlip * BF = new BitFlip() ;
	Rearrange * R = new Rearrange() ;

	Individual * aptr = new Individual() ;
	Individual * bptr = new Individual() ;

	aptr = execute( &a, BF, k1 ) ;
	aptr = execute( &a, R, k1 ) ;

	bptr = execute( &b, BF, k2 ) ;
	bptr = execute( &b, R, k2 ) ;


	std::cout << aptr -> getString() << bptr -> getString() << bptr -> getMaxOnes() << std::endl ;

	return 0 ;
}

Individual * execute(Individual * indPtr, Mutator * mPtr, int k)
{
	Individual ind ;

	ind = mPtr -> mutate( *indPtr, k ) ;

	Individual* indptr = &ind ;
	
	return indptr ;
}