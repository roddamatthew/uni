#ifndef JOURNAL_H
#define JOURNAL_H

class Journal : public Book
{
private:
	int Volume;
public:
	Journal();
	Journal(std::string title, std::string author, int n, int v);
	void print();
};
#endif //JOURNAL_H