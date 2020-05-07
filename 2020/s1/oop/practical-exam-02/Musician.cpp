#include <iostream>
#include "Musician.h"

Musician::Musician(){
	musinstrument="null";
	musexperience=0;
}



// a constructor that takes the instrument played and the years of experience
Musician::Musician(std::string instrument, int experience){
	musinstrument=instrument;
	musexperience=experience;
}      


std::string Musician::get_instrument(){
	return musinstrument;
}

int Musician::get_experience(){
	return musexperience;
}

Musician::~Musician(){};
