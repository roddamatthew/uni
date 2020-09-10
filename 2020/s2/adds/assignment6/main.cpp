#include "Individual.h"
// #include "Mutator.h"

#include <iostream>

int main(){
	Individual DNA ( "0110" ) ;

	std::cout << DNA.getString() << std::endl ;
	std::cout << DNA.getBit( 0 ) << " " << DNA.getBit( 1 ) << std::endl ;
	DNA.flipBit( 0 ) ;
	std::cout << DNA.getString() << std::endl ;

	return 0 ;
}