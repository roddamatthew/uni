#include <iostream>
#include <string>
using namespace std;

extern void print_class(std::string courses[4], std::string students[], int report_card[][4], int nstudents);

int main(){
	string courses[4]={"maths", "science", "music", "PE"};
	string students[4]={"andrew","matthew","leo","aaron"};
	int nstudents=4;
	int report_card[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};

print_class(courses,students,report_card,nstudents);

	return 0;

}