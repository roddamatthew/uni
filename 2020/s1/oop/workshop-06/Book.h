#ifndef BOOK_H
#define BOOK_H

#include <string>

// Class definition for a book
class Book
{
public:
	// Book constructor
	Book(std::string book_name, int book_pages);
	
	std::string name;
	int pages;
	// bool borrowed;
	
	// void borrowbook();
	// void returnbook();
	
	~Book();

};
#endif //BOOK_H