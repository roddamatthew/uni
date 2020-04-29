#include <iostream>
#include "meerkat.h"
#include "cart.h"

using namespace std;

int main(){
	meerkat *A, *B;
	cart *E;

	string nameA, nameB;
	int ageA, ageB;

	A = new meerkat();
	A -> setName("A");
	A -> setAge(1);

	nameA=A -> getName();
	ageA=A -> getAge();

	B = new meerkat();
	B -> setName("B");
	B -> setAge(2);

	nameB=B -> getName();
	ageB=B -> getAge();

	E = new cart();
	E -> addMeerkat(*A);
	E -> addMeerkat(*B);
	E -> addMeerkat(*A);
	E -> addMeerkat(*B);

	E -> printMeerkats();

	return 0;

}