#ifndef MUSICIAN_H
#define MUSICIAN_H

#include <iostream>

class Musician
{
public:
	std::string musinstrument;
	int musexperience;

	Musician();                  // a default constructor 

	// a constructor that takes the instrument played and the years of experience
	Musician(std::string instrument, int experience);      

	std::string get_instrument();    // returns the instrument played

	int get_experience();       // returns the number of years experience

	~Musician();                //A default destructor

};
#endif //MUSICIAN_H