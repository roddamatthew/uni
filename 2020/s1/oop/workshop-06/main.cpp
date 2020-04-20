#include <iostream>
#include "Book.h"
#include "Library.h"

using namespace std;

int main(){
	Book *A, *B;
	A = new Book("A", 15);
	B = new Book("B", 20);

	Library *C;
	C = new Library("1", "2", "3");

	return 0;
}