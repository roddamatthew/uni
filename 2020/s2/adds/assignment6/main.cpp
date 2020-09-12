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
	*indPtr = mPtr -> mutate( *indPtr, k ) ;
	
	return indPtr ;
}

int main(){
	string str ;
	string binarystr1 ;
	string kone ;
	int k1 ;
	string binarystr2 ;
	string ktwo ;
	int k2 ;

	// Input processing
	int i = 0 ;

	getline(cin, str);

	while( str[i] != ' ' )
	{
		binarystr1 += str[i] ;
		i++ ;
	}
	i++ ;

	while( str[i] != ' ' )
	{
		kone += str[i] ;
		i++ ;
	}
	i++ ;

	while( str[i] != ' ' )
	{
		binarystr2 += str[i] ;
		i++ ;
	}
	i++ ;

	while( str[i] != ' ' && i < str.length() )
	{
		ktwo += str[i] ;
		i++ ;
	}

	k1 = stoi( kone ) ;
	k2 = stoi( ktwo ) ;


	// Initialise classes
	BitFlip * BF = new BitFlip() ;
	Rearrange * R = new Rearrange() ;

	Individual *  DNA1 = new Individual( binarystr1 ) ;
	Individual *  DNA2 = new Individual( binarystr2 ) ;

	// Perform mutations
	Individual * aptr = execute( DNA1, BF, k1 ) ;
	string a = aptr -> getString() ;
	Individual *  DNA3 = new Individual( a ) ;

	Individual * bptr = execute( DNA2, R, k2 ) ;
	string b = bptr -> getString() ;
	Individual *  DNA4 = new Individual( b ) ;

	// Output
	std::cout << DNA3 -> getString() << " " << DNA4 -> getString() << " " << DNA4 -> getMaxOnes() << std::endl ;

	return 0 ;
}