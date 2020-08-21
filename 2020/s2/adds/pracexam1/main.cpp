#include "Book.h"
#include "Journal.h"
#include <string>
#include <iostream>

extern bool equals(Book b1, Book b2);

int main() {
	
	Book b1("Norton’s Star Atlas", "A.P. Norton", 510);
	Book b2("Pocket Sky Atlas", "J. Sinot", 511);

	Journal j1("Journal 1", "Matt", 512, 1);
	Journal j2("Journal 2", "Jerry", 513, 4);
	
	if (equals(b1, b2)) {
		std::cout << "The books are the same" << std::endl ;
	}else{
		std::cout << "The books are different" << std::endl ;
	}

	b1.print();
	b2.print();

	j1.print();
	j2.print();

	return 0;
}