#include <iostream>
#include "cart.h"
#include "meerkat.h"

using namespace std;

//Implemetation of cart constructor
cart::cart()
{
	meerkat *cat1, *cat2, *cat3, *cat4, *cat5;
	cat1=new meerkat();
	cat2=new meerkat();
	cat3=new meerkat();
	cat4=new meerkat();
	cat5=new meerkat();

	counter=0;
}


//Implementation of meerkat adder
bool cart::addMeerkat(meerkat cat)
{
	bool roomFormeerkat=true;

	if(counter>4){
		roomFormeerkat=false;
		return roomFormeerkat;
	}else{
		switch (counter)
		{
			case 0:
			cat1=cat;
			break;

			case 1:
			cat2=cat;
			break;

			case 2:
			cat3=cat;
			break;

			case 3:
			cat4=cat;
			break;

			case 4:
			cat5=cat;
			break;
		}

		counter++;
	}

	return roomFormeerkat;
}


//Implementation of emptying cart functionality
void cart::emptyCart()
{
	cat1=meerkat();
	cat2=meerkat();
	cat3=meerkat();
	cat4=meerkat();
	cat5=meerkat();

	counter=0;
}


//Implementation of print meerkat's functionality
void cart::printMeerkats()
{
	std::cout << cat1.getName() << " " << cat1.getAge() <<std::endl;
	std::cout << cat2.getName() << " " << cat2.getAge() <<std::endl;
	std::cout << cat3.getName() << " " << cat3.getAge() <<std::endl;
	std::cout << cat4.getName() << " " << cat4.getAge() <<std::endl;
	std::cout << cat5.getName() << " " << cat5.getAge() <<std::endl;
}