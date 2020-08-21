#include "Book.h"
#include <string>
#include <iostream>

Book :: Book() {}

Book :: Book(std::string title, std::string author, int n){
	Title = title;
	Author = author;
	callNo = n;
}

void Book :: print(){
	std::cout << "Book details:" << std::endl;
	std::cout << "Title: " << Title << ", by: " << Author << std::endl;
	std::cout << "callNo: " << callNo << std::endl;
}

std::string Book :: getTitle(){
	return Title;
}

std::string Book :: getAuthor(){
	return Author;
}