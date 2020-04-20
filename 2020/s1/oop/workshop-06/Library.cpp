#include <iostream>
#include "Library.h"
#include "Book.h"

using namespace std;

// Implementation of library constructor

Library::Library(string book1, string book2, string book3)
{
	name=book1;
	name2=book2;
	name3=book3;
}

Library::~Library()
{
}