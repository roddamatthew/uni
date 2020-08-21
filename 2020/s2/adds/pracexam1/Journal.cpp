#include "Book.h"
#include "Journal.h"

#include <iostream>

Journal :: Journal() {}

Journal :: Journal(std::string title, std::string author, int n, int v)
	: Book(title, author, n)
	{
	Volume = v;
	}

void Journal :: print(){
	Book :: print();
	std::cout << "Volume: " << Volume << std::endl;
}