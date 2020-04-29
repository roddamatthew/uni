#ifndef CART_H
#define CART_H

#include <string>
#include <iostream>
#include "meerkat.h"

using namespace std;

class cart
{
public:
	meerkat cat1, cat2, cat3, cat4, cat5;
	int counter;
	
	cart();                         // create an empty cart object
	bool addMeerkat(meerkat cat);   // adds a meerkat to the cart, returns false if full
	void emptyCart();               // remove all meerkats from the cart
	void printMeerkats();           // print the name, a space, the age, then a new line for each meerkat in the order they were added
};

#endif //CART_H