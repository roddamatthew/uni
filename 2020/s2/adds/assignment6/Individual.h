#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>
#include <list>

class Individual
{
private:
	std::list<int> binaryString ;

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