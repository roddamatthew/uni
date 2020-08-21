#include <string>
#include "Book.h"

bool equals(Book b1, Book b2){
	if(b1.getTitle().compare(b2.getTitle()) == 0){
		if(b1.getAuthor().compare(b2.getAuthor()) == 0){
			return true;
		}
	}else{
		return false;
	}
}