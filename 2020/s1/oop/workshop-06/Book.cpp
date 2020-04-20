#include <iostream>
#include "Book.h"

using namespace std;

// Implementation of Book constructor

Book::Book(string book_name, int book_pages)
{
	name = book_name;
	pages = book_pages;
	// borrowed = false;
}

// // Implementation of the borrow function
// void Book::borrowbook()
// {
// 	if(borrowed==false){
// 		borrowed=true;
// 		std::cout << "You have borrowed the book: " << name << "." << std::endl;
// 	}else{
// 		std::cout << name << "has already been borrowed.";
// 	}
// }

// // Implementation of the borrow function
// void Book::returnbook()
// {
// 	if(borrowed==true){
// 		borrowed=false;
// 		std::cout << "You have returned the book: " << name << "." << std::endl;
// 	}else{
// 		std::cout << name << "has not been borrowed and cannot be returned.";
// 	}
// }

// Implementation of the default destructor
Book::~Book()
{
}