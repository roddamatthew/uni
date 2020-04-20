#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include "Book.h"

// Class definition for a library
class Library
{
public:
	// Library constructor
	Library(std::string book1, std::string book2, std::string book3);

	std::string name1;
	std::string name2;
	std::string name3;

	// void borrowbook(Book bookname);
	// void returnbook(Book bookname);

	~Library();

};
#endif //LIBRARY_H