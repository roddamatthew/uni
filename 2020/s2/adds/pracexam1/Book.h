#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
	std::string Title;
	std::string Author;
	int callNo;
public:
	Book();
	Book(std::string title, std::string author, int n);
	void print();
	std::string getTitle();
	std::string getAuthor();
};
#endif //BOOK_H