#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>

class Individual
{
private:
	std::string binaryString ;

public:
	Individual() ;

	Individual( int length ) ;

	Individual( std::string code ) ;

	std::string getString() ;

	int getBit( int pos ) ;

	void flipBit( int pos ) ;

	int getMaxOnes() ;

	int getLength() ;
};

#endif //INDIVIDUAL_H