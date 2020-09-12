#include "Individual.h"
#include "Mutator.h"
#include "BitFlip.h"
#include "BitFlipProb.h"
#include "Rearrange.h"

#include <iostream>
#include <string>

using namespace std;

Individual * execute(Individual * indPtr, Mutator * mPtr, int k)
{
	string str = indPtr -> getString() ;

	Individual ind = Individual( str );

	ind = mPtr -> mutate( *indPtr, k ) ;
	
	return &ind ;
}

int main(){
	string str ;
	string binarystr1 ;
	int k1 ;
	string binarystr2 ;
	int k2 ;

	int i = 0 ;

	getline(cin, str);

	while( str[i] != ' ' )
	{
		binarystr1 += str[i] ;
		i++ ;
	}
	i++ ;
	
	k1 = str[ i ] - 48 ;
	i = i + 2 ;

	while( str[i] != ' ' )
	{
		binarystr2 += str[i] ;
		i++ ;
	}

	i++ ;
	k2 = str[ i ] - 48 ;

	BitFlip * BF = new BitFlip() ;
	Rearrange * R = new Rearrange() ;

	Individual *  DNA1 = new Individual( binarystr1 ) ;
	Individual *  DNA2 = new Individual( binarystr2 ) ;

	Individual * aptr = execute( DNA1, BF, k1 ) ;
	string a = aptr -> getString() ;
	Individual *  DNA3 = new Individual( a ) ;

	Individual * bptr = execute( DNA2, R, k2 ) ;
	string b = bptr -> getString() ;
	Individual *  DNA4 = new Individual( b ) ;

	std::cout << DNA3 -> getString() << " " << DNA4 -> getString() << " " << DNA4 -> getMaxOnes() << std::endl ;

	return 0 ;
}