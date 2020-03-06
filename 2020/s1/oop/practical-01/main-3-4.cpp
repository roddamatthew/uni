#include <iostream>

extern void passorfail(char grade);

int main(){
	char grade1=65;
	char grade2=67;
	char grade3=69;
	char grade4=110;

	passorfail(grade1);
	passorfail(grade2);
	passorfail(grade3);
	passorfail(grade4);

	return 0;
}