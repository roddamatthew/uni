#include "Book.h"
#include "Journal.h"
#include <string>
#include <iostream>

extern bool equals(Book b1, Book b2);

int main() {
	Book b1("Norton’s Star Atlas", "A.P. Norton", 510);
	Book b2("Pocket Sky Atlas", "J. Sinot", 511);
	Book b3("Norton’s Star Atlas", "A.P. Norton", 510);

	// Creating new journal objects
	Journal j1("Journal 1", "Matt", 512, 1);
	Journal j2("Journal 2", "Jerry", 513, 2);
	Journal j3("Journal 2", "Jerry", 513, 3);
	
	if (equals(b1, b2) == true) {
		std::cout << "The books are the same" << std::endl ;
	}else{
		std::cout << "The books are different" << std::endl ;
	}

	std::cout << std::endl;
	std::cout << "Printing Book 1" << std::endl;
	b1.print();
	
	std::cout << std::endl;
	std::cout << "Printing Book 2" << std::endl;
	b2.print();

	// Calling the Journal version of print() on the journal objects created
	std::cout << std::endl;
	std::cout << "Printing Journal 1" <<std::endl;
	j1.print();

	std::cout << std::endl;
	std::cout << "Printing Journal 2" <<std::endl;
	j2.print();

	// Calling the Book version of print() on the journal objects created
	// Note how command line omits the information about the volume as the journal is treated as a book
	std::cout << std::endl;
	std::cout << "Printing Journal 1 as a Book" <<std::endl;
	j1.Book :: print();
	
	std::cout << std::endl;
	std::cout << "Printing Journal 2 as a Book" <<std::endl;
	j2.Book :: print();
	
	std::cout << std::endl;
	std::cout << "Testing if Journal 1 and Journal 2 are equal" <<std::endl;

	// Using the journals as books and calling the equals function
	if (equals(j1, j2)) {
		std::cout << "The books are the same" << std::endl ;
	}else{
		std::cout << "The books are different" << std::endl ;
	}

	std::cout << std::endl;
	std::cout << "Testing if Journal 2 and Journal 3 are equal"<< std::endl;

	// Using the identical journals as books and calling the equals function
	// Note that this returns the books are the same even though the volumes are different.
	// This is because passing the journals as books slices the volume information and the equals function returns true.
	if (equals(j2, j3)) {
		std::cout << "The books are the same" << std::endl ;
	}else{
		std::cout << "The books are different" << std::endl ;
	}

	return 0;
}